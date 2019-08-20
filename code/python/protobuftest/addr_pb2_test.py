#! /usr/bin/python

import addr_pb2
import sys


def ListPeople(address_book):
    for person in address_book.people:
        print("Person ID:", person.id)
        print("  Name:", person.name)
        if person.HasField('email'):
            print("  E-mail address:", person.email)

        for phone_number in person.phones:
            if phone_number.type == addr_pb2.Person.MOBILE:
                print("  Mobile phone #: ", phone_number.number)
            elif phone_number.type == addr_pb2.Person.HOME:
                print("  Home phone #: ", phone_number.number)
            elif phone_number.type == addr_pb2.Person.WORK:
                print("  Work phone #: ", phone_number.number)


def AddItem(person):
    person.id = 1234
    person.name = "Yi"

    person.email = "a@b.c"

    phone_number = person.phones.add()
    phone_number.number = "1233456"
    phone_number.type = addr_pb2.Person.MOBILE

    phone_number = person.phones.add()
    phone_number.number = "AVD1233456"
    phone_number.type = addr_pb2.Person.HOME


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:", sys.argv[0], "ADDRESS_BOOK_FILE")
        sys.exit(-1)

    address_book = addr_pb2.AddressBook()

    try:
        f = open(sys.argv[1], "rb")
        print(sys.argv[1] + ": exist, reading the conent")
        address_book.ParseFromString(f.read())
        f.close()

        ListPeople(address_book)
    except IOError:
        print(sys.argv[1] + ": doesn't exist, creating a new one.")

        # Add an address.
        AddItem(address_book.people.add())
        ListPeople(address_book)

        print(sys.argv[1] + ": save file")
        f = open(sys.argv[1], "wb")
        f.write(address_book.SerializeToString())
        f.close()
