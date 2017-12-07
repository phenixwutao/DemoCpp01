using System;
using System.Web;
using System.Globalization;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Security.Cryptography;
using System.Text;

namespace DuoAuth
{
  /// <summary>
  /// Duo Hash class for Duo MFA autheitcation to generate signature based on various keys
  /// </summary>
  public class DuoHash
  {
    private DateTime date;
    private string ikey;    // Duo integration key
    private string skey;    // Duo secret
    private string host;    // Duo API host
    private string method;  // Duo method GET/POST
    private string path;    // Duo call path e.g. "/auth/v2/check", "/auth/v2/auth"
    private Dictionary<string, string> parameters;  // parameters e.g. "username" = "ZZZ"

    public DuoHash(string ikey, string skey, string host, string method, string path, DateTime date, Dictionary<string, string> parameters)
    {
      this.date = date;
      this.ikey   = ikey;
      this.skey   = skey;
      this.host   = host;
      this.method = method;
      this.path   = path;
      this.parameters = parameters;
    }

    protected string CanonicalizeParams()
    {
      var ret = new List<String>();
      foreach (KeyValuePair<string, string> pair in parameters)
      {
        string p = String.Format("{0}={1}",
                                 HttpUtility.UrlEncode(pair.Key),
                                 HttpUtility.UrlEncode(pair.Value));
        // Signatures require upper-case hex digits.
        p = Regex.Replace(p,
                          "(%[0-9A-Fa-f][0-9A-Fa-f])",
                          c => c.Value.ToUpperInvariant());
        // Escape only the expected characters.
        p = Regex.Replace(p,
                          "([!'()*])",
                          c => "%" + Convert.ToByte(c.Value[0]).ToString("X"));
        p = p.Replace("%7E", "~");
        // UrlEncode converts space (" ") to "+". The
        // signature algorithm requires "%20" instead. Actual
        // + has already been replaced with %2B.
        p = p.Replace("+", "%20");
        ret.Add(p);
      }
      ret.Sort(StringComparer.Ordinal);
      return string.Join("&", ret.ToArray());
    }

    protected string CanonicalizeRequest(string canon_params, string date)
    {
      string[] lines = {
                date,
                method.ToUpperInvariant(),
                host.ToLower(),
                path,
                canon_params,
            };
      string canon = String.Join("\n", lines);
      return canon;
    }


    private static string Encode64(string plaintext)
    {
      byte[] plaintext_bytes = ASCIIEncoding.ASCII.GetBytes(plaintext);
      string encoded = System.Convert.ToBase64String(plaintext_bytes);
      return encoded;
    }

    private static string DateToRFC822(DateTime date)
    {
      // Can't use the "zzzz" format because it adds a ":"
      // between the offset's hours and minutes.
      string date_string = date.ToString(
          "ddd, dd MMM yyyy HH:mm:ss", CultureInfo.InvariantCulture);
      int offset = TimeZone.CurrentTimeZone.GetUtcOffset(date).Hours;
      string zone;
      // + or -, then 0-pad, then offset, then more 0-padding.
      if (offset < 0)
      {
        offset *= -1;
        zone = "-";
      }
      else
      {
        zone = "+";
      }
      zone += offset.ToString(CultureInfo.InvariantCulture).PadLeft(2, '0');
      date_string += " " + zone.PadRight(5, '0');
      return date_string;
    }

    private string HmacSign(string data)
    {
      byte[] key_bytes = ASCIIEncoding.ASCII.GetBytes(this.skey);
      HMACSHA1 hmac = new HMACSHA1(key_bytes);

      byte[] data_bytes = ASCIIEncoding.ASCII.GetBytes(data);
      hmac.ComputeHash(data_bytes);

      string hex = BitConverter.ToString(hmac.Hash);
      return hex.Replace("-", "").ToLower();
    }

    protected string Sign(string canon_params, string date)
    {
      string canon = CanonicalizeRequest(canon_params, date);
      string sig = this.HmacSign(canon);
      string auth = this.ikey + ':' + sig;
      return "Basic " + Encode64(auth);
    }

    public static string GetDuoDateTime(DateTime date)
    {
      return DateToRFC822(date);
    }

    public string GetDuoSignature()
    {
      string canon_params = CanonicalizeParams();
      string date_string = DateToRFC822(this.date);
      date_string = "Thu, 07 Dec 2017 20:30:09 -0000";
      return Sign(canon_params, date_string);
    }
  }

} // namespace
