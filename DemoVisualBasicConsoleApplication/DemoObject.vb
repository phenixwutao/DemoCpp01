Module ObjectModule
  Public Class DemoObject
    Public Property Name As String
    Public Property Identifier As String
    Public Property UniqueNumber As UShort
    Public Function Group() As String
      Dim sGroup As String = ""
      Select Case UniqueNumber
        Case Is = 1
          sGroup = "development"
        Case Is = 2
          sGroup = "customer support"
        Case Is = 3
          sGroup = "marketing"
        Case Is = 4
          sGroup = "implementation"
      End Select
      Return sGroup
    End Function

    Public Function IsEmployed() As Boolean
      Return UniqueNumber <> 0
    End Function

  End Class
End Module

