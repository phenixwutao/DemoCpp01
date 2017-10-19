import People

def Ch00_DemoPeopleClass():
  print("-----------------------------------",Ch00_DemoPeopleClass.__name__)
  dev = People.People("John", "Green", 28, 0, "CF")
  dev.DisplayFullName()
  print("its age ", dev.GetAge())
