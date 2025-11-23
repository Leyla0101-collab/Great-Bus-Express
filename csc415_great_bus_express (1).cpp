#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

void displayTotalFee();
float calculateTotalFee(char lCode);
float applyDiscount(float fee, char discountCode);
void generateReceipt(string name, string email, string seat, string time, int month, int day, int phoneNumber, char gender, int pax, int age, float totalFee, char seatType, char discountCode);

bool isValidDate(int month, int day);
bool isSeatAvailable(const int* seats, int size, int seat);

int main()
{
    // Declare the variables
    string name, email, seat, time;
    char customer[31], lCode, gender, nextCustomer, seatType, choice, discountCode;
    int date, day, pax, phoneNumber, age, month;
    float totalFee;

    // Declare and initialize the arrays for singleSeats and doubleSeats
    int singleSeats[11] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    int doubleSeats[20] = { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

    bool isSeatValid = false; // Variable to check if the entered seat is valid

    do
    {
        cout << "\n\n##############################################################" << endl;
        cout << "\t WELCOME TO GREAT BUS EXPRESS SERVICE" << endl;
        cout << "##############################################################\n\n";

        cout << "##############################################################" << endl;
        cout << "\tPLEASE ENTER ALL YOUR DETAILS" << endl;
        cout << "##############################################################\n\n";

        displayTotalFee();

        cout << "Enter your name: "; //enter the full name
        cin.ignore(); // clear newline from previous input (in case)
        getline(cin, name);

        cout << "Enter your email: ";
        cin >> email;
        cout << "You entered: " << email << endl;

        cout << "Enter your phone number(+60): ";
        cin >> phoneNumber;

        cout << "Enter your gender (F-female or M-male): ";
        cin >> gender;

        cout << "Enter your age: ";
        cin >> age;

        cout << "Enter the seat type (S-singleSeats or D-doubleSeats): ";
        cin >> seatType;

        int seat = 0;

        if (seatType == 'S' || seatType == 's')
        {
            cout << "Available single seats: ";
            for (int i = 0; i < 11; i++) {
                cout << singleSeats[i] << " ";
            }
            cout << endl;

            cout << "Enter the seat number: ";
            cin >> seat;

            // Validate if the entered seat is available
            isSeatValid = isSeatAvailable(singleSeats, 11, seat);
            if (!isSeatValid) {
                cout << "Invalid seat selection for single seats." << endl;
            }
        }
        else if (seatType == 'D' || seatType == 'd')
        {
            cout << "Available double seats: ";
            for (int i = 0; i < 20; i++) {
                cout << doubleSeats[i] << " ";
            }
            cout << endl;

            cout << "Enter the seat number: ";
            cin >> seat;

            // Validate if the entered seat is available
            isSeatValid = isSeatAvailable(doubleSeats, 20, seat);
            if (!isSeatValid) {
                cout << "Invalid seat selection for double seats." << endl;
            }
        }
        else
        {
            cout << "Invalid seat type entered." << endl;
        }

        cout << "Select the time of departure:\n";
        cout << "1. 9:00 am\n";
        cout << "2. 13:00 pm\n";
        cout << "3. 17:00 pm\n";
        cout << "4. 20:00 pm\n";
        cout << "Enter your choice (1-4): ";
        int timeChoice;
        cin >> timeChoice;

        switch (timeChoice)
        {
        case 1:
            time = "9:00 am";
            break;
        case 2:
            time = "13:00 pm";
            break;
        case 3:
            time = "17:00 pm";
            break;
        case 4:
            time = "20:00 pm";
            break;
        default:
            cout << "Invalid time choice. Setting default time to 9:00 am.\n";
            time = "9:00 am";
            break;
        }

        // Input and validate the month
        cout << "Select the month:\n";
        cout << "1. January\n";
        cout << "2. February\n";
        cout << "3. March\n";
        cout << "4. April\n";
        cout << "5. May\n";
        cout << "6. June\n";
        cout << "7. July\n";
        cout << "8. August\n";
        cout << "9. September\n";
        cout << "10. October\n";
        cout << "11. November\n";
        cout << "12. December\n";
        cout << "Enter your choice (1-12): ";
        cin >> month;

        // Input and validate the day
        do
        {
            cout << "Enter the day: ";
            cin >> day;
        } while (!isValidDate(month, day));

        cout << "Enter the pax: ";
        cin >> pax;

        cout << "Are you a student? (Y-yes, N-no): ";
        cin >> discountCode;

        cout << "Select the location code:\n";
        cout << "A. Malacca Central\t\tPrice: RM 16.00\n";
        cout << "B. Kuala Perlis Bus Terminal\tPrice: RM 40.00\n";
        cout << "C. Southern Integrated Terminal\tPrice: RM 3.30\n";
        cout << "D. Alor Setar Terminal Bus\tPrice: RM 40.00\n";
        cout << "E. Kuantan Central Bus Terminal\tPrice: RM 28.10\n";
        cout << "F. Larkin Central Johor\t\tPrice: RM 35.00\n";
        cout << "G. Ipoh Amanjaya Terminal\tPrice: RM 29.80\n";
        cout << "H. Penang Central Bus Terminal\tPrice: RM 37.00\n";
        cout << "I. Terminal One Seremban\tPrice: RM 8.40\n";
        cout << "J. Kuala Terengganu Terminal\tPrice: RM 36.10\n";
        cout << "K. Kota Bahru Bus Terminal\tPrice: RM 34.00\n";
        cout << "Enter your choice (A-K): ";
        cin >> lCode;

        // Calculate total fee based on the location code
        totalFee = calculateTotalFee(lCode);

        // Apply discount for students
        totalFee = applyDiscount(totalFee, discountCode);

        // Display total fee
        cout << "Total Fee: RM " << fixed << setprecision(2) << totalFee << endl;
        generateReceipt(name, email, to_string(seat), time, month, day, phoneNumber, gender, pax, age, totalFee, seatType, discountCode);

        cout << "ENJOY YOUR JOURNEY!" << endl;
        cout << "THANK YOU FOR USING OUR SERVICE!" << endl;
        cout << "PLEASE GET YOUR ONLINE BOARDING PASS ON OUR WEBSITE..." << endl;

        cout << "Do you want to repeat the service for the next customer [y-yes, n-no]: ";
        cin >> nextCustomer;

    } while (nextCustomer == 'y' || nextCustomer == 'Y');

    return 0;
}

float calculateTotalFee(char lCode)
{
    float fee = 0.0f;
    // Calculate total fee based on the location code
    switch (toupper(lCode))
    {
    case 'A':
        fee = 16.00f;
        break;
    case 'B':
        fee = 40.00f;
        break;
    case 'C':
        fee = 3.30f;
        break;
    case 'D':
        fee = 40.00f;
        break;
    case 'E':
        fee = 28.10f;
        break;
    case 'F':
        fee = 35.00f;
        break;
    case 'G':
        fee = 29.80f;
        break;
    case 'H':
        fee = 37.00f;
        break;
    case 'I':
        fee = 8.40f;
        break;
    case 'J':
        fee = 36.10f;
        break;
    case 'K':
        fee = 34.00f;
        break;
    default:
        cout << "Invalid location code." << endl;
        break;
    }
    return fee;
}

float applyDiscount(float fee, char discountCode)
{
    if (discountCode == 'Y' || discountCode == 'y')
    {
        fee = fee * 0.85f; // Apply 15% discount for students
    }
    else
    {
        // if not a student, no discount is applied (0% discount)
    }
    return fee;
}

void displayTotalFee()
{
    cout << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "\t location Code \t\t Description" << endl;
    cout << "A. Malacca Central\t\tPrice: RM 16.00" << endl;
    cout << "B. Kuala Perlis Bus Terminal\tPrice: RM 40.00" << endl;
    cout << "C. Southern Integrated Terminal\tPrice: RM 3.30" << endl;
    cout << "D. Alor Setar Terminal Bus\tPrice: RM 40.00" << endl;
    cout << "E. Kuantan Central Bus Terminal\tPrice: RM 28.10" << endl;
    cout << "F. Larkin Central Johor\t\tPrice: RM 35.00" << endl;
    cout << "G. Ipoh Amanjaya Terminal\tPrice: RM 29.80" << endl;
    cout << "H. Penang Central Bus Terminal\tPrice: RM 37.00" << endl;
    cout << "I. Terminal One Seremban\tPrice: RM 8.40" << endl;
    cout << "J. Kuala Terengganu Terminal\tPrice: RM 36.10" << endl;
    cout << "K. Kota Bahru Bus Terminal\tPrice: RM 34.00" << endl;
    cout << endl;
}

void generateReceipt(string name, string email, string seat, string time, int month, int day, int phoneNumber, char gender, int pax, int age, float totalFee, char seatType, char discountCode)
{
    cout << endl;
    cout << "------------------------ Receipt ------------------------" << endl;
    cout << "Name: " << name << endl; //name
    cout << "Email: " << email << endl;
    cout << "Phone Number: +60 " << phoneNumber << endl;
    cout << "Gender: " << gender << endl;
    cout << "Age: " << age << endl;
    cout << "Seat Type: " << (seatType == 'S' ? "Single" : "Double") << endl;
    cout << "Seat Number: " << seat << endl;
    cout << "Time of Departure: " << time << endl;
    cout << "Month: " << month << endl;
    cout << "Day: " << day << endl;
    cout << "Pax: " << pax << endl;
    cout << "Discount Applied: " << ((discountCode == 'Y' || discountCode == 'y') ? "Yes (Student - 15%)" : "No") << endl;
    cout << "Total Fee: RM " << fixed << setprecision(2) << totalFee << endl;
    cout << "------------------------ Great Bus Express ------------------------" << endl;
    cout << endl;
}

bool isValidDate(int month, int day)
{
    if (month < 1 || month > 12)
        return false;

    if (day < 1 || day > 31)
        return false;

    // April, June, September, November have 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
        return false;

    // February check (not handling leap years precisely)
    if (month == 2 && (day < 1 || day > 29))
        return false;

    return true;
}

bool isSeatAvailable(const int* seats, int size, int seat)
{
    for (int i = 0; i < size; i++)
    {
        if (seats[i] == seat)
            return true;
    }
    return false;
}
