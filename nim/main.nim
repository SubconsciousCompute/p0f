import strformat

type
    Person = object
        name: string
        age: Natural

let people = [
    Person(name: "John", age: 45),
    Person(name: "Dilawar", age: 30)
]

for person in people:
    echo(fmt"{person.name} in {person.age} years old")
