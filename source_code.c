#include <stdio.h>
#include <string.h>
#define MAX_SEATS 2
struct Hostel
{
int hostelNo;
char name[50];
char gender[10];
char block;
char plot[20];
char flat[20];
};
struct Hostel hostels[] =
{
{101, "Bashundhara Girls Hostel 1", "Girl", 'A', "Plot-12", "Flat-4A"},
{102, "Bashundhara Girls Hostel 2", "Girl", 'B', "Plot-15", "Flat-3B"},
{103, "Bashundhara Girls Hostel 3", "Girl", 'C', "Plot-18", "Flat-5C"},
{104, "Bashundhara Girls Hostel 4", "Girl", 'D', "Plot-22", "Flat-2D"},
{201, "Bashundhara Boys Hostel 1", "Boy", 'A', "Plot-35", "Flat-3A"},
{202, "Bashundhara Boys Hostel 2", "Boy", 'B', "Plot-39", "Flat-5B"},
{203, "Bashundhara Boys Hostel 3", "Boy", 'C', "Plot-43", "Flat-2C"},
{204, "Bashundhara Boys Hostel 4", "Boy", 'D', "Plot-47", "Flat-6D"}
};
/* Count bookings for a hostel */
int getBookedSeats(int hostelNo)
{
FILE *file;
char line[200];
int bookingID;
int bookedHostel;
int count = 0;
file = fopen("bookings.txt", "r");
if (file == NULL)
{
return 0;
}
while (fgets(line, sizeof(line), file) != NULL)
{
if (sscanf(line, "%d|%d", &bookingID, &bookedHostel) == 2)
{
if (bookedHostel == hostelNo)
{
count++;
}
}
}
fclose(file);
return count;
}
/* Generate next booking ID */
int getNextBookingID()
{
FILE *file;
char line[100];
int bookingID;
int hostelNo;
int nextID = 1001;
file = fopen("bookings.txt", "r");
if (file == NULL)
{
return nextID;
}
while (fgets(line, sizeof(line), file) != NULL)
{
if (sscanf(line, "%d|%d", &bookingID, &hostelNo) == 2)
{
if (bookingID >= nextID)
{
nextID = bookingID + 1;
}
}
}
fclose(file);
return nextID;
}
/* Save booking information */
int saveBooking(int bookingID,
int hostelNo,
char name[],
char phone[],
char roomType[],
char furniture[],
char food[],
int totalCost)
{
FILE *file;
file = fopen("bookings.txt", "a");
if (file == NULL)
{
printf("\nError: Could not save booking.\n");
return 0;
}
fprintf(file, "%d|%d|%s|%s|%s|%s|%s|%d\n",
bookingID,
hostelNo,
name,
phone,
roomType,
furniture,
food,
totalCost);
fclose(file);
return 1;
}
int main()
{
int genderChoice;
int hostelChoice;
int hostelIndex = -1;
int roomChoice;
int furnitureChoice;
int foodChoice;
int bookChoice;
int confirm;
int roomPrice;
int furnitureCost;
int foodCost;
int blockCost;
int totalCost;
int bookedSeats;
int remainingSeats;
int i;
char gender[10];
char roomType[30];
char furniture[20];
char food[20];
char name[50];
char phone[20];
int bookingID;
printf("\n============================================\n");
printf(" BASHUNDHARA HOSTEL FINDER\n");
printf(" & BOOKING SYSTEM\n");
printf("============================================\n");
/* Select gender */
printf("\nAre you looking for a hostel for?\n");
printf("1. Boy\n");
printf("2. Girl\n");
printf("\nEnter choice: ");
scanf("%d", &genderChoice);
if (genderChoice == 1)
{
strcpy(gender, "Boy");
}
else if (genderChoice == 2)
{
strcpy(gender, "Girl");
}
else
{
printf("\nInvalid choice!\n");
return 0;
}
/* Show available hostels */
printf("\n========================================\n");
printf(" %s HOSTELS\n", gender);
printf("========================================\n");
for (i = 0; i < 8; i++)
{
if (strcmp(hostels[i].gender, gender) == 0)
{
bookedSeats = getBookedSeats(hostels[i].hostelNo);
remainingSeats = MAX_SEATS - bookedSeats;
if (remainingSeats > 0)
{
printf("\nHostel No. : %d", hostels[i].hostelNo);
printf("\nName : %s", hostels[i].name);
printf("\nBlock : %c", hostels[i].block);
printf("\nPlot : %s", hostels[i].plot);
printf("\nFlat : %s", hostels[i].flat);
printf("\nSeats Left : %d/%d\n",
remainingSeats, MAX_SEATS);
}
}
}
/* Select hostel */
printf("\nEnter hostel number: ");
scanf("%d", &hostelChoice);
for (i = 0; i < 8; i++)
{
if (hostels[i].hostelNo == hostelChoice &&
strcmp(hostels[i].gender, gender) == 0)
{
hostelIndex = i;
break;
}
}
if (hostelIndex == -1)
{
printf("\nInvalid hostel selection!\n");
return 0;
}
/* Check availability */
bookedSeats = getBookedSeats(hostels[hostelIndex].hostelNo);
if (bookedSeats >= MAX_SEATS)
{
printf("\n============================================\n");
printf(" HOSTEL FULL\n");
printf("============================================\n");
printf("Sorry! %s already has %d/%d students.\n",
hostels[hostelIndex].name,
bookedSeats,
MAX_SEATS);
return 0;
}
remainingSeats = MAX_SEATS - bookedSeats;
printf("\n============================================\n");
printf(" HOSTEL AVAILABILITY\n");
printf("============================================\n");
printf("Total Seats : %d\n", MAX_SEATS);
printf("Booked Seats : %d\n", bookedSeats);
printf("Remaining Seats : %d\n", remainingSeats);
/* Room type */
printf("\n========================================\n");
printf(" ROOM TYPE\n");
printf("========================================\n");
printf("1. Master Bed - 10000 Tk\n");
printf("2. Semi-Master Bed - 8000 Tk\n");
printf("3. Partition Room - 5000 Tk\n");
printf("\nEnter choice: ");
scanf("%d", &roomChoice);
if (roomChoice == 1)
{
strcpy(roomType, "Master Bed");
roomPrice = 10000;
}
else if (roomChoice == 2)
{
strcpy(roomType, "Semi-Master Bed");
roomPrice = 8000;
}
else if (roomChoice == 3)
{
strcpy(roomType, "Partition Room");
roomPrice = 5000;
}
else
{
printf("\nInvalid room type!\n");
return 0;
}
/* Furniture */
printf("\n========================================\n");
printf(" FURNITURE\n");
printf("========================================\n");
printf("1. Furnished (+1000 Tk)\n");
printf("2. Non-Furnished (+0 Tk)\n");
printf("\nEnter choice: ");
scanf("%d", &furnitureChoice);
if (furnitureChoice == 1)
{
strcpy(furniture, "Furnished");
furnitureCost = 1000;
}
else if (furnitureChoice == 2)
{
strcpy(furniture, "Non-Furnished");
furnitureCost = 0;
}
else
{
printf("\nInvalid choice!\n");
return 0;
}
/* Food */
printf("\n========================================\n");
printf(" FOOD FACILITY\n");
printf("========================================\n");
printf("1. With Food (+5000 Tk)\n");
printf("2. Without Food (+0 Tk)\n");
printf("\nEnter choice: ");
scanf("%d", &foodChoice);
if (foodChoice == 1)
{
strcpy(food, "With Food");
foodCost = 5000;
}
else if (foodChoice == 2)
{
strcpy(food, "Without Food");
foodCost = 0;
}
else
{
printf("\nInvalid choice!\n");
return 0;
}
/* Block charge */
if (hostels[hostelIndex].block == 'A' ||
hostels[hostelIndex].block == 'B')
{
blockCost = 1000;
}
else
{
blockCost = 500;
}
/* Total cost */
totalCost = roomPrice + furnitureCost + foodCost + blockCost;
/* Show details */
printf("\n============================================\n");
printf(" HOSTEL DETAILS\n");
printf("============================================\n");
printf("Hostel No. : %d\n", hostels[hostelIndex].hostelNo);
printf("Hostel Name : %s\n", hostels[hostelIndex].name);
printf("Block : %c\n", hostels[hostelIndex].block);
printf("Plot No. : %s\n", hostels[hostelIndex].plot);
printf("Flat No. : %s\n", hostels[hostelIndex].flat);
printf("--------------------------------------------\n");
printf("Room Type : %s\n", roomType);
printf("Furniture : %s\n", furniture);
printf("Food : %s\n", food);
printf("--------------------------------------------\n");
printf("Room Price : %d Tk\n", roomPrice);
printf("Furniture : +%d Tk\n", furnitureCost);
printf("Food : +%d Tk\n", foodCost);
printf("Block Charge : +%d Tk\n", blockCost);
printf("--------------------------------------------\n");
printf("TOTAL COST : %d Tk/month\n", totalCost);
printf("============================================\n");
/* Booking decision */
printf("\nWould you like to book this hostel?\n");
printf("1. Yes\n");
printf("2. No\n");
printf("\nEnter choice: ");
scanf("%d", &bookChoice);
if (bookChoice == 2)
{
printf("\nNever mind, thanks for trusting us!\n");
return 0;
}
if (bookChoice != 1)
{
printf("\nInvalid choice!\n");
return 0;
}
/* Student information */
getchar();
printf("\n========================================\n");
printf(" BOOKING INFORMATION\n");
printf("========================================\n");
printf("Enter your name: ");
fgets(name, sizeof(name), stdin);
name[strcspn(name, "\n")] = '\0';
printf("Enter your phone number: ");
scanf("%19s", phone);
/* Booking details */
printf("\n============================================\n");
printf(" BOOKING DETAILS\n");
printf("============================================\n");
printf("Name : %s\n", name);
printf("Phone : %s\n", phone);
printf("Hostel : %s\n", hostels[hostelIndex].name);
printf("Hostel No. : %d\n", hostels[hostelIndex].hostelNo);
printf("Block : %c\n", hostels[hostelIndex].block);
printf("Plot No. : %s\n", hostels[hostelIndex].plot);
printf("Flat No. : %s\n", hostels[hostelIndex].flat);
printf("Room Type : %s\n", roomType);
printf("Furniture : %s\n", furniture);
printf("Food : %s\n", food);
printf("Monthly Cost : %d Tk\n", totalCost);
printf("============================================\n");
/* Final confirmation */
printf("\nAre you sure you want to confirm this booking?\n");
printf("1. Confirm Booking\n");
printf("2. Cancel Booking\n");
printf("\nEnter choice: ");
scanf("%d", &confirm);
if (confirm == 1)
{
bookingID = getNextBookingID();
if (saveBooking(bookingID,
hostels[hostelIndex].hostelNo,
name,
phone,
roomType,
furniture,
food,
totalCost))
{
printf("\n============================================\n");
printf(" BOOKING CONFIRMED!\n");
printf("============================================\n");
printf("Booking ID : %d\n", bookingID);
printf("Name : %s\n", name);
printf("Phone Number : %s\n", phone);
printf("Hostel : %s\n", hostels[hostelIndex].name);
printf("Hostel No. : %d\n", hostels[hostelIndex].hostelNo);
printf("Block : %c\n", hostels[hostelIndex].block);
printf("Room : %s\n", roomType);
printf("Furniture : %s\n", furniture);
printf("Food : %s\n", food);
printf("Monthly Cost : %d Tk\n", totalCost);
printf("--------------------------------------------\n");
printf("Thank you for choosing our hostel!\n");
printf("We look forward to having you with us.\n");
printf("============================================\n");
}
else
{
printf("\nBooking was not confirmed because it could not be saved.\n");
}
}
else if (confirm == 2)
{
printf("\nBooking cancelled.\n");
}
else
{
printf("\nInvalid choice!\n");
}
return 0;
}
