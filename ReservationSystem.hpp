#ifndef RESERVATION_REQUEST_HPP
#define RESERVATION_REQUEST_HPP

#include "ReservationRequest.hpp"

class ReservationSystem {

private:
    int room_count;
    int* room_capacities;

    struct Reservation {
        std::string course_name;
        std::string weekday;
        int start_hour;
        int end_hour;
        int room_index;
    };

    Reservation* reservations;
    int reservation_count;

public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

};

#endif