#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
struct Bus { 
 int busNo; 
 char source[30]; 
 char destination[30]; 
 int totalSeats; 
 int availableSeats; 
 float fare; 
 int seats[50]; 
}; 
void showMenu(); 
void bookTicket(struct Bus *buses, int num); 
void cancelTicket(struct Bus *buses, int num); 
void viewStatus(struct Bus *buses, int num); 
void saveToFile(struct Bus *bus, int seatNo, char name[]); 
void printTicket(struct Bus *bus, int seatNo, char name[]); 
int main() { 
 struct Bus buses[3] = { 
 {101, "CityA", "CityB", 30, 30, 250.0}, 
 {102, "CityC", "CityD", 40, 40, 300.0}, 
pg. 7
 {103, "CityE", "CityF", 50, 50, 350.0} 
 }; 
 for (int i = 0; i < 3; i++) { 
 for (int j = 0; j < buses[i].totalSeats; j++) { 
 buses[i].seats[j] = 0; 
 } 
 } 
 int choice; 
 while (1) { 
 showMenu(); 
 scanf("%d", &choice); 
 switch (choice) { 
 case 1: 
 bookTicket(buses, 3); 
 break; 
 case 2: 
 cancelTicket(buses, 3); 
 break; 
 case 3: 
 viewStatus(buses, 3); 
 break; 
 case 4: 
 printf("Exiting the program. Thank you!\n"); 
 exit(0); 
 default: 
 printf("Invalid choice! Please try again.\n"); 
 } 
 } 
 return 0; 
} 
void showMenu() { 
 printf("\n=== BUS RESERVATION SYSTEM ===\n"); 
 printf("1. Book a Ticket\n"); 
 printf("2. Cancel a Ticket\n"); 
 printf("3. View Bus Status\n"); 
pg. 8
 printf("4. Exit\n"); 
 printf("Enter your choice: "); 
} 
void bookTicket(struct Bus *buses, int num) { 
 int busNo, seatNo; 
 char name[50]; 
 printf("Enter your name: "); 
 scanf("%s", name); 
 printf("Enter Bus Number: "); 
 scanf("%d", &busNo); 
 struct Bus *bus = NULL; 
 for (int i = 0; i < num; i++) { 
 if (buses[i].busNo == busNo) { 
 bus = &buses[i]; 
 break; 
 } 
 } 
 if (bus == NULL) { 
 printf("Bus not found!\n"); 
 return; 
 } 
 printf("Enter seat number (1-%d): ", bus->totalSeats); 
 scanf("%d", &seatNo); 
 if (seatNo < 1 || seatNo > bus->totalSeats) { 
 printf("Invalid seat number!\n"); 
 return; 
 } 
 if (bus->seats[seatNo - 1] == 1) { 
 printf("Seat already booked! Try another seat.\n"); 
 return; 
 } 
 bus->seats[seatNo - 1] = 1; 
 bus->availableSeats--; 
 printf("Seat %d booked successfully on Bus %d!\n", seatNo, 
busNo); 
 printTicket(bus, seatNo, name); 
 saveToFile(bus, seatNo, name); 
pg. 9
} 
void cancelTicket(struct Bus *buses, int num) { 
 int busNo, seatNo; 
 printf("Enter Bus Number: "); 
 scanf("%d", &busNo); 
 struct Bus *bus = NULL; 
 for (int i = 0; i < num; i++) { 
 if (buses[i].busNo == busNo) { 
 bus = &buses[i]; 
 break; 
 } 
 } 
 if (bus == NULL) { 
 printf("Bus not found!\n"); 
 return; 
 } 
 printf("Enter seat number to cancel: "); 
 scanf("%d", &seatNo); 
 if (seatNo < 1 || seatNo > bus->totalSeats) { 
 printf("Invalid seat number!\n"); 
 return; 
 } 
 if (bus->seats[seatNo - 1] == 0) { 
 printf("That seat is not booked yet!\n"); 
 return; 
 } 
 bus->seats[seatNo - 1] = 0; 
 bus->availableSeats++; 
 printf("Seat %d on Bus %d has been cancelled.\n", seatNo, 
busNo); 
} 
void viewStatus(struct Bus *buses, int num) { 
 int busNo; 
 printf("Enter Bus Number: "); 
 scanf("%d", &busNo); 
 for (int i = 0; i < num; i++) { 
pg. 10
 if (buses[i].busNo == busNo) { 
 printf("\nBus %d: %s to %s\n", buses[i].busNo, 
buses[i].source, buses[i].destination); 
 printf("Total Seats: %d\n", buses[i].totalSeats); 
 printf("Available Seats: %d\n", buses[i].availableSeats); 
 printf("Fare: %.2f\n", buses[i].fare); 
 printf("Seats (O = Free, X = Booked):\n"); 
 for (int j = 0; j < buses[i].totalSeats; j++) { 
 printf("%c", buses[i].seats[j] ? 'X' : 'O'); 
 if ((j + 1) % 10 == 0) printf("\n"); 
 } 
 printf("\n"); 
 return; 
 } 
 } 
 printf("Bus not found!\n"); 
} 
void saveToFile(struct Bus *bus, int seatNo, char name[]) { 
 FILE *fp = fopen("bookings.txt", "a"); 
 if (fp == NULL) { 
 printf("Error opening file!\n"); 
 return; 
 } 
 fprintf(fp, "Name: %s | Bus: %d | Seat: %d | Fare: %.2f\n", 
name, bus->busNo, seatNo, bus->fare); 
 fclose(fp); 
} 
void printTicket(struct Bus *bus, int seatNo, char name[]) { 
 printf("\n===== YOUR TICKET =====\n"); 
 printf("Passenger Name: %s\n", name); 
 printf("Bus Number: %d\n", bus->busNo); 
 printf("Route: %s to %s\n", bus->source, bus->destination); 
 printf("Seat Number: %d\n", seatNo); 
 printf("Fare: %.2f\n", bus->fare); 
 printf("=======================\n"); 
}