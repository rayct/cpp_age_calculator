// Version: 1.0
// In this version of the program, we've made use of the ctime and chrono libraries to handle date and time operations.
// We've also used string streams to convert


// #include <iostream>
// #include <ctime>
// #include <chrono>
// #include <string>
// #include <sstream>

// using namespace std;

// // Convert string in UK format to tm struct
// tm strToTm(string str) {
//     stringstream ss(str);
//     int day, month, year;
//     char sep;
//     ss >> day >> sep >> month >> sep >> year;
//     tm date = {};
//     date.tm_mday = day;
//     date.tm_mon = month - 1;
//     date.tm_year = year - 1900;
//     return date;
// }

// // Format tm struct as string in US format
// string tmToStr(tm date) {
//     char buf[11];
//     strftime(buf, 11, "%m-%d-%Y", &date);
//     return string(buf);
// }

// // Calculate age in years from birthdate and current date
// int calculateAge(tm birthdate, tm today) {
//     int age = today.tm_year - birthdate.tm_year;
//     if (today.tm_mon < birthdate.tm_mon || (today.tm_mon == birthdate.tm_mon && today.tm_mday < birthdate.tm_mday)) {
//         age--;
//     }
//     return age;
// }

// // Calculate day of the week the user was born on
// string calculateDayOfWeek(tm birthdate) {
//     char buf[20];
//     strftime(buf, 20, "%A", &birthdate);
//     return string(buf);
// }

// // Calculate number of days until next birthday from birthdate and current date
// int calculateDaysUntilNextBirthday(tm birthdate, tm today) {
//     tm nextBirthday = birthdate;
//     nextBirthday.tm_year = today.tm_year;
//     if (nextBirthday < today) {
//         nextBirthday.tm_year++;
//     }
//     int daysUntilBirthday = (int)difftime(mktime(&nextBirthday), mktime(&today)) / (60 * 60 * 24);
//     if (daysUntilBirthday < 0) {
//         nextBirthday.tm_year++;
//         daysUntilBirthday = (int)difftime(mktime(&nextBirthday), mktime(&today)) / (60 * 60 * 24);
//     }
//     return daysUntilBirthday;
// }

// int main() {
//     // Prompt user for their date of birth in UK format
//     string birthdateStr;
//     cout << "Enter your date of birth (DD-MM-YYYY): ";
//     cin >> birthdateStr;

//     // Convert birthdate to tm struct
//     tm birthdate = strToTm(birthdateStr);

//     // Get today's date
//     time_t now = time(nullptr);
//     tm today = *localtime(&now);

//     // Calculate age in years
//     int age = calculateAge(birthdate, today);

//     // Calculate day of the week the user was born on
//     string dayOfWeek = calculateDayOfWeek(birthdate);

//     // Calculate number of days until next birthday
//     int daysUntilBirthday = calculateDaysUntilNextBirthday(birthdate, today);

//     // Format birthdate to US format
//     string birthdateUsStr = tmToStr(birthdate);

//     // Print results
//     cout << "You were born on a " << dayOfWeek << "." << endl;
//     cout << "You are currently " << age << " years old." << endl;
//     cout << "There are " << daysUntilBirthday << " days until your next birthday." << endl;
//     cout << "Your birthdate in US format is: " << birthdateUsStr << "." << endl;

//     return 0;
// }

// Version: 1.0.2
// This version of the program uses references instead of copies of tm structs,
// avoids unnecessary calculations using std::chrono,
// ses string literals instead of creating std::string objects from char arrays, and uses const where appropriate.

#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

// Calculates the age in years between two dates
int calculateAge(const tm& birthdate, const tm& today) {
    int age = today.tm_year - birthdate.tm_year;
    if (today.tm_mon < birthdate.tm_mon ||
        (today.tm_mon == birthdate.tm_mon && today.tm_mday < birthdate.tm_mday)) {
        age--;
    }
    return age;
}

// Calculates the number of days until the next birthday
int calculateDaysUntilNextBirthday(const tm& birthdate, const tm& today) {
    // Get next birthday for this year
    tm nextBirthday = birthdate;
    nextBirthday.tm_year = today.tm_year;
    if (nextBirthday < today) {
        nextBirthday.tm_year++;
    }

    // Calculate days until next birthday using std::chrono
    auto nextBirthdayTime = std::chrono::system_clock::from_time_t(std::mktime(&nextBirthday));
    auto todayTime = std::chrono::system_clock::from_time_t(std::mktime(&today));
    auto diff = std::chrono::duration_cast<std::chrono::hours>(nextBirthdayTime - todayTime).count();
    int daysUntilBirthday = diff / 24;

    return daysUntilBirthday;
}

// Converts a tm struct to a string in the format "MM-DD-YYYY"
string tmToStr(const tm& date) {
    char buf[11];
    strftime(buf, 11, "%m-%d-%Y", &date);
    return buf;
}

// Calculates the day of the week for a given date
string calculateDayOfWeek(const tm& birthdate) {
    char buf[20];
    strftime(buf, 20, "%A", &birthdate);
    return buf;
}

int main() {
    // Get birthdate from user input
    cout << "Enter your birthdate (MM/DD/YYYY): ";
    tm birthdate = {};
    char delimiter;
    cin >> std::get_time(&birthdate, "%m/%d/%Y%c");

    // Get current date
    time_t now = time(nullptr);
    tm today = *localtime(&now);

    // Calculate age and days until next birthday
    int age = calculateAge(birthdate, today);
    int daysUntilBirthday = calculateDaysUntilNextBirthday(birthdate, today);

    // Output results
    cout << "You were born on " << tmToStr(birthdate) << ", which was a " << calculateDayOfWeek(birthdate) << endl;
    cout << "You are currently " << age << " years old." << endl;
    cout << "Your next birthday is in " << daysUntilBirthday << " days." << endl;

    return 0;
}

