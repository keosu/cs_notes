#include <fstream>
#include <iostream>
#include <string>
#include "addr.pb.h"
using namespace std;

void ListPeople(const tutorial::AddressBook& address_book) {
  for (int i = 0; i < address_book.people_size(); i++) {
    const tutorial::Person& person = address_book.people(i);

    cout << "Person ID: " << person.id() << endl;
    cout << "  Name: " << person.name() << endl;
    if (person.has_email()) {
      cout << "  E-mail address: " << person.email() << endl;
    }

    for (int j = 0; j < person.phones_size(); j++) {
      const tutorial::Person::PhoneNumber& phone_number = person.phones(j);

      switch (phone_number.type()) {
        case tutorial::Person::MOBILE:
          cout << "  Mobile phone #: ";
          break;
        case tutorial::Person::HOME:
          cout << "  Home phone #: ";
          break;
        case tutorial::Person::WORK:
          cout << "  Work phone #: ";
          break;
      }
      cout << phone_number.number() << endl;
    }
  }
}
// This function fills in a Person message based on user input.
void AddItem(tutorial::Person* person) {
  person->set_id(123456);

  person->set_name("my_name");
  person->set_email("a@b.c");

  tutorial::Person::PhoneNumber* phone_number = person->add_phones();
  phone_number->set_number("3456");
  phone_number->set_type(tutorial::Person::MOBILE);

  phone_number = person->add_phones();
  phone_number->set_number("7890");
  phone_number->set_type(tutorial::Person::HOME);
}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " addr_book_FILE" << endl;
    return -1;
  }

  // Add an address.
  tutorial::AddressBook address_book;

  // Read the existing address book.
  fstream input(argv[1], ios::in | ios::binary);
  if (address_book.ParseFromIstream(&input)) {
    cout << "addr file exist, read from it" << endl;
    ListPeople(address_book);
  } else {
    cout << "addr file doesn't exist, create new one" << endl;

    AddItem(address_book.add_people());

    // Write the new address book back to disk.
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!address_book.SerializeToOstream(&output)) {
      cerr << "Failed to write address book." << endl;
      return -1;
    }
  }

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}