//
//  medium.cpp
//  hwk 3
//
//  Created by Ankush Bharadwaj on 5/9/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

enum CallType {
    VOICE, TEXT
};

//medium stuff
class Medium
{
public:
    Medium(string id);
    virtual ~Medium() {};
    virtual string connect() const = 0;
    string id() const;
    virtual string transmit(string msg) const = 0;
private:
    string m_id;
};

Medium::Medium(string id) {
    m_id = id;
}

string Medium::id() const {
    return m_id;
}

//phone stuff
class Phone : public Medium
{
public:
    Phone(string number, CallType call):Medium(number),m_number(number),m_call(call) {};
    virtual ~Phone() { cout << "Destroying the phone " << m_number << "." << endl;};
    string connect() const;
    string transmit(string msg) const;
private:
    string m_number;
    CallType m_call;
};

string Phone::connect() const {
    return "Call";
}

string Phone::transmit(string msg) const {
    string output = "";
    if (m_call == 0)
        output += "voice: ";
    else if(m_call == 1)
        output += "text: ";
    output += msg;
    return output;
}

//twitter stuff
class TwitterAccount : public Medium
{
public:
    TwitterAccount(string account_name):Medium(account_name),m_account_name(account_name){};
    virtual ~TwitterAccount() { cout << "Destroying the Twitter account " << m_account_name << "." << endl;};
    string connect() const;
    string transmit(string msg) const;
private:
    string m_account_name;
};

string TwitterAccount::connect() const {
    return "Tweet";
}

string TwitterAccount::transmit(string msg) const {
    string output = "";
    output += "text: " + msg;
    return output;
}

//email stuff
class EmailAccount : public Medium
{
public:
    EmailAccount(string email_id):Medium(email_id),m_email_id(email_id){};
    virtual ~EmailAccount() { cout << "Destroying the email account " << m_email_id << "." << endl;};
    string connect() const;
    string transmit(string msg) const;
private:
    string m_email_id;
};

string EmailAccount::connect() const {
    return "Email";
}

string EmailAccount::transmit(string msg) const {
    string output = "";
    output += "text: " + msg;
    return output;
}



 void send(const Medium* m, string msg)
 {
 cout << m->connect() << " using id " << m->id()
 << ", sending " << m->transmit(msg) << endl;
 }

int main()
{
    Medium* media[4];
    media[0] = new TwitterAccount("UCLABruinAlert");
    // Phone users may prefer messages to be left as voice or text.
    media[1] = new Phone("(310) 825 3894", VOICE);
    media[2] = new Phone("(213) 389 9060", TEXT);
    media[3] = new EmailAccount("jbroon@ucla.edu");
    
     cout << "Send the message." << endl;
     for (int k = 0; k < 4; k++)
     send(media[k], "Major power outage in West L.A.");
    
    // Clean up the media before exiting
    cout << "Cleaning up." << endl;
     for (int k = 0; k < 4; k++)
     delete media[k];
}



