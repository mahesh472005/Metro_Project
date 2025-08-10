#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STATIONS 50
#define MAX_NAME_LEN 32
#define MAX_PASSENGERS 10
#define STATION_FILE "stations.txt"
#define TICKET_FILE "tickets.txt"
#define BASE_FARE 10
#define RATE_PER_STATION 10
#define RETURN_DISCOUNT 0.15  // 15% discount for return
#define STUDENT_DISCOUNT 0.20 // 20% discount for students

// Color output macros (works with ANSI-compatible terminals)
#define RESET "\033[0m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"

char stations[MAX_STATIONS][MAX_NAME_LEN];
int num_stations = 0;

typedef struct {
  char name[MAX_NAME_LEN];
  int is_student;
} Passenger;

typedef struct {
  int journey_type;
  int start;
  int end;
  int num_passengers;
  Passenger passengers[MAX_PASSENGERS];
  int total_fare;
  time_t timestamp;
  long ticket_id;
} Ticket;

// ** Utility to trim newline from fgets **
void trim_newline(char *str) {
  int len = strlen(str);
  if (len > 0 && str[len - 1] == '\n')
    str[len - 1] = '\0';
}

// ** Read stations from file **
void loadStations() {
  FILE *fp = fopen(STATION_FILE, "r");
  if (!fp) {
    printf(RED "Error: Could not open %s\n" RESET, STATION_FILE);
    exit(1);
  }
  num_stations = 0;
  while (fgets(stations[num_stations], MAX_NAME_LEN, fp)) {
    trim_newline(stations[num_stations]);
    num_stations++;
    if (num_stations >= MAX_STATIONS)
      break;
  }
  fclose(fp);
}

// ** Display main menu **
void displayMenu() {
  printf(CYAN "-------------------------------------------\n");
  printf("|    Mumbai Metro Online Ticketing System |\n");
  printf("-------------------------------------------\n" RESET);
  printf("1. Buy Ticket\n");
  printf("2. Exit\n");
}

// ** Display stations **
void displayStations() {
  printf(GREEN "Stations:\n" RESET);
  for (int i = 0; i < num_stations; i++) {
    printf("%2d. %s\n", i + 1, stations[i]);
  }
}

// ** Calculate fare **
double calculateFare(int start, int end, int journeyType, Passenger *passengers,
                     int num_passengers) {
  int distance = abs(end - start);
  double fare = BASE_FARE + (distance * RATE_PER_STATION);

  // Apply discounts for students and return journeys
  int student_count = 0;
  for (int i = 0; i < num_passengers; i++) {
    if (passengers[i].is_student)
      student_count++;
  }
  int normal_count = num_passengers - student_count;
  double total_fare =
      fare * normal_count + fare * (1.0 - STUDENT_DISCOUNT) * student_count;

  if (journeyType == 2) { // Return journey
    total_fare *= 2;
    total_fare *= (1.0 - RETURN_DISCOUNT);
  }
  return total_fare;
}

// ** Print ticket **
void printTicket(Ticket t) {
  printf(CYAN "\n-------------------------------------------\n" RESET);
  printf(YELLOW "|           YOUR TICKET                   |\n" RESET);
  printf(CYAN "-------------------------------------------\n" RESET);

  printf("From Station   : %s\n", stations[t.start - 1]);
  printf("To Station     : %s\n", stations[t.end - 1]);
  printf("Journey Type   : %s\n", t.journey_type == 1 ? "One-way" : "Return");
  printf("No. Passengers : %d\n", t.num_passengers);
  printf("Passengers     :\n");
  for (int i = 0; i < t.num_passengers; i++) {
    printf("  - %s", t.passengers[i].name);
    if (t.passengers[i].is_student)
      printf(" (Student, %.0f%% off)", STUDENT_DISCOUNT * 100);
    printf("\n");
  }
  printf(GREEN "Total Fare     : Rs %.2lf\n" RESET, (double)t.total_fare);
  printf("Date/Time      : %s", ctime(&t.timestamp));
  printf("Ticket ID      : %ld\n", t.ticket_id);
  printf("Journey must start within 60 minutes.\n");
  printf("Thank you for choosing Mumbai Metro!\n");
  printf(CYAN "-------------------------------------------\n" RESET);
}

// ** Save ticket to file **
void saveTicket(Ticket t) {
  FILE *fp = fopen(TICKET_FILE, "a");
  if (!fp)
    return;
  fprintf(fp, "TicketID: %ld | ", t.ticket_id);
  fprintf(fp, "From: %s | To: %s | ", stations[t.start - 1],
          stations[t.end - 1]);
  fprintf(fp, "Type: %s | ", t.journey_type == 1 ? "Oneway" : "Return");
  fprintf(fp, "Passengers: %d | Names: ", t.num_passengers);
  for (int i = 0; i < t.num_passengers; i++) {
    fprintf(fp, "%s%s", t.passengers[i].name,
            t.passengers[i].is_student ? "(S)" : "");
    if (i != t.num_passengers - 1)
      fprintf(fp, ", ");
  }
  fprintf(fp, " | Fare: Rs %.2lf | Date: %s", (double)t.total_fare,
          ctime(&t.timestamp));
  fclose(fp);
}

// ** Ticket Purchase Flow **
void buyTicket() {
  Ticket ticket;
  int valid = 0;

  // Journey Type Menu
  printf(CYAN "\nSelect Journey Type:\n" RESET);
  printf("1. One-way\n");
  printf("2. Return (%.0f%% discount)\n", RETURN_DISCOUNT * 100);
  printf("\nEnter choice: ");
  scanf("%d", &ticket.journey_type);

  // Input validation
  if (ticket.journey_type < 1 || ticket.journey_type > 2) {
    printf(RED "Invalid journey type.\n" RESET);
    return;
  }

  displayStations();
  printf("\nSelect starting station number: ");
  scanf("%d", &ticket.start);
  if (ticket.start < 1 || ticket.start > num_stations) {
    printf(RED "Invalid selection.\n" RESET);
    return;
  }

  printf("Select destination station number: ");
  scanf("%d", &ticket.end);
  if (ticket.end < 1 || ticket.end > num_stations ||
      ticket.end == ticket.start) {
    printf(RED "Invalid destination.\n" RESET);
    return;
  }

  printf("\nEnter number of passengers (max %d): ", MAX_PASSENGERS);
  scanf("%d", &ticket.num_passengers);
  if (ticket.num_passengers < 1 || ticket.num_passengers > MAX_PASSENGERS) {
    printf(RED "Invalid number.\n" RESET);
    return;
  }

  // Clear input buffer before fgets
  while (getchar() != '\n')
    ;

  // Passenger details
  for (int i = 0; i < ticket.num_passengers; i++) {
    printf("Enter passenger #%d name: ", i + 1);
    fgets(ticket.passengers[i].name, MAX_NAME_LEN, stdin);
    trim_newline(ticket.passengers[i].name);

    printf("Is %s a student (Y/N)? ", ticket.passengers[i].name);
    char student_resp;
    scanf(" %c", &student_resp);
    ticket.passengers[i].is_student =
        (student_resp == 'Y' || student_resp == 'y') ? 1 : 0;
    while (getchar() != '\n')
      ;
  }

  ticket.timestamp = time(NULL);
  ticket.ticket_id = ticket.timestamp + rand() % 10000;
  ticket.total_fare =
      (int)calculateFare(ticket.start, ticket.end, ticket.journey_type,
                         ticket.passengers, ticket.num_passengers);

  printTicket(ticket);
  saveTicket(ticket);

  printf(YELLOW "\nTicket has been saved to '%s'.\n" RESET, TICKET_FILE);
}

// ** Main Function **
int main() {
  loadStations();
  srand(time(NULL));

  while (1) {
    system("cls || clear");
    displayMenu();
    printf("\nChoose an option: ");
    int opt;
    scanf("%d", &opt);
    if (opt == 1) {
      buyTicket();
      printf(GREEN "\nPress Enter to continue..." RESET);
      while (getchar() != '\n')
        ;
      getchar();
    } else if (opt == 2) {
      printf(YELLOW
             "Thank you for using Mumbai Metro Online Ticketing!\n" RESET);
      break;
    } else {
      printf(RED "Invalid option!\n" RESET);
      printf("Press Enter to continue...");
      while (getchar() != '\n')
        ;
      getchar();
    }
  }
  return 0;
}
