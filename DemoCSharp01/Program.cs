using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DuoAuth;

namespace DemoCSharp01
{
  class Program
  {
    static void Main(string[] args)
    {
      string ikey = "DI69KPJ4IULGLQYW34JD";
      string skey = "nMz9aTvyDA4mlyuWNhyE2fvhh9gJcfwtpu788MUL";
      string host = "api-fd5b4799.duosecurity.com";
      string method = "POST";
      string path = "/auth/v2/enroll";
      DateTime date = System.DateTime.UtcNow;
      System.Collections.Generic.Dictionary<string, string> pams = new System.Collections.Generic.Dictionary<string, string>();
      pams.Add("username", "ZZZ");
      DuoHash duoHash = new DuoHash(ikey, skey, host, method, path, date, pams);
      string strSignnature = duoHash.GetDuoSignature();
      string strDate = DuoHash.GetDuoDateTime(date);
      Console.WriteLine("Date: " + date.ToString());
      Console.WriteLine("Sign: " + strSignnature);
      Console.WriteLine("Duo Date: " + strDate);
    }
  }
}
