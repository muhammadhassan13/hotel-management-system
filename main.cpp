#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <fstream>
using namespace std;

//Date class
class Date {
public:
	int day, month, year;
	
	Date() : day(1), month(1), year(2025) {}
	Date(int d, int m, int y) : day(d), month(m), year(y) {
		adjustDate();
	}
		
	void adjustDate() {
		while (day > 30) {
			day -= 30;
            month++;
        }
        while (month > 12) {
            month -= 12;
            year++;
        }
    }

    bool isValid() const {
        return (day >= 1 && day <= 30 && month >= 1 && month <= 12 && year >= 2023);
    }

    int daysBetween(const Date& other) const {
        int d1 = year * 360 + month * 30 + day;
        int d2 = other.year * 360 + other.month * 30 + other.day;
        return d2 - d1;
    }

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator>(const Date& other) const {
        if (year != other.year) return year > other.year;
        if (month != other.month) return month > other.month;
        return day > other.day;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    void display() const {
        cout << day << "/" << month << "/" << year;
    }
};

//Room class (abstract base class)
class Room {
protected:
    int roomNumber;
    string type;
    double pricePerDay;
    bool isAvailable;
    string features;
    bool underMaintenance;

public:
    Room(int num, string t, double price, string feat): roomNumber(num), type(t), pricePerDay(price), isAvailable(true), features(feat), underMaintenance(false) {}

    virtual ~Room() {}
    
    virtual double calculateBill(int days) const = 0;	//pure virtual function
    virtual void displayInfo() const = 0;	//pure virtual function

    void bookRoom() { isAvailable = false; }
    void vacateRoom() { isAvailable = true; }

    bool isRoomAvailable() const { return isAvailable && !underMaintenance; }

    void toggleMaintenance(bool status) { underMaintenance = status; }
    bool isUnderMaintenance() const { return underMaintenance; }

    void setPrice(double price) { pricePerDay = price; }
    double getPrice() const { return pricePerDay; }

    int getRoomNumber() const { return roomNumber; }
    string getType() const { return type; }
};

//StandardRoom class (derived from Room)
class StandardRoom : public Room {
public:
    StandardRoom(int num): Room(num, "Standard", 3000, "TV and Wi-Fi") {}

    double calculateBill(int days) const override {
        return pricePerDay * days;
    }

    void displayInfo() const override {
        cout << "Standard Room #" << roomNumber << " - " << "(Includes " << features << "), Price per day: Rs. " << pricePerDay << endl;
    }
};

//DeluxeRoom class (derived from Room)
class DeluxeRoom : public Room {
    double serviceFee;
    double luxuryTax;

public:
    DeluxeRoom(int num): Room(num, "Deluxe", 5000, "Smart Lock and Ocean View"), serviceFee(1000), luxuryTax(0.1) {}

    double calculateBill(int days) const override {
        return (pricePerDay * days) + serviceFee + (luxuryTax * pricePerDay * days);
    }

    void displayInfo() const override {
        cout << "Deluxe Room #" << roomNumber << " - " << "(Includes " << features << "), Price per day: Rs. " << pricePerDay << ", Service Fee: Rs. " << serviceFee << ", Luxury Tax: " << (luxuryTax * 100) << "%" << endl;
    }
};

//SuiteRoom class (derived from Room)
class SuiteRoom : public Room {
    double luxuryTax;

public:
    SuiteRoom(int num): Room(num, "Suite", 8000, "Mini Bar and Lounge Access"), luxuryTax(0.15) {}

    double calculateBill(int days) const override {
        return (pricePerDay * days) + (luxuryTax * pricePerDay * days);
    }

    void displayInfo() const override {
        cout << "Suite Room #" << roomNumber << " - " << "(Includes " << features << "), Price per day: Rs. " << pricePerDay << ", Luxury Tax: " << (luxuryTax * 100) << "%" << endl;
    }
};

//Service class (abstract base class)
class Service {
public:
    virtual string getServiceName() const = 0;
    virtual double getServiceCharge() const = 0;
    virtual ~Service() {}
};

//LaundryService class (derived from Service)
class LaundryService : public Service {
public:
    string getServiceName() const override {
		return "Laundry";
	}
    double getServiceCharge() const override {
		return 500.0;
	}
};

//MealService class (derived from Service)
class MealService : public Service {
public:
    string getServiceName() const override {
		return "Meal";
	}
    double getServiceCharge() const override {
		return 1000.0;
	}
};

//TransportService class (derived from Service)
class TransportService : public Service {
public:
    string getServiceName() const override {
		return "Transport";
	}
    double getServiceCharge() const override {
		return 1500.0;
	}
};