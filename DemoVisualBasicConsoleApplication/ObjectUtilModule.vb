Module ObjectUtilModule
  ''' <summary>
  ''' Use DemoObject class from Module "ObjectModule"
  ''' </summary>
  ''' <returns></returns>
  Public Function Ch00_DemoModuleClass() As Int16

    Dim obj As New ObjectModule.DemoObject()
    obj.UniqueNumber = 1
    Console.WriteLine("Object group is: " + obj.Group())
    Return obj.UniqueNumber

  End Function
End Module
