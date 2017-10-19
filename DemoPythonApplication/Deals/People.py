class People:
  #_firstname = ""
  #_surname = ""
  #_age = 0
  #_identifier = -1;
  #_department = "";

  def __init__(self, firstname, surname, age, identifier, department):
    self._firstname = firstname
    self._surname = surname
    self._age = age
    self._identifier = identifier
    self._department = department

  def DisplayFullName(self):
    print("Fullname: ", self._firstname, self._surname)

  def GetAge(self):
    print("Age: ", self._age)
    return self._age
