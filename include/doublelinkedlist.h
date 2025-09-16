#pragma once
#include <string>
using namespace std;

// ======================= Structs =======================
struct Ticket {
    int id;
    string customerName;
    Ticket* next;
    Ticket* prev;
};

struct Seat {
    int id;
    bool isBooked;
    Seat* next;
    Seat* prev;
};

struct Showtime {
    int id;
    string movieName;
    string time;
    Showtime* prev;
    Showtime* next;
};

// ======================= Class =======================
class Cinema {
private:
    Ticket* ticketHead;
    Seat* seatHead;
    Showtime* showtimeHead;

public:
    Cinema();
    ~Cinema();

    // --------- CRUD Vé ---------
    void createTicket(int id, string customer);
    void readTickets() const;
    void updateTicket(int id, string newName);
    void deleteTicket(int id);

    // --------- CRUD Ghế ---------
    void createSeat(int id);
    void readSeats() const;
    void updateSeat(int id, bool booked);
    void deleteSeat(int id);

    // --------- CRUD Suất chiếu ---------
    void createShowtime(int id, string movie, string time);
    void readShowtimes() const;
    void updateShowtime(int id, string newMovie, string newTime);
    void deleteShowtime(int id);

    // --------- Dọn dẹp ---------
    void clearTickets();
    void clearSeats();
    void clearShowtimes();
};
