#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"

// construtor
ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;
    this->room_capacities = new int[room_count];

    for(int i = 0; i < room_count; i++){
        this->room_capacities[i] = room_capacities[i];
    }

    this->reservation_count = 0;
    this->reservations = new Reservation[70 * room_count];

    for(int i = 0; i < (70 * room_count); i++){
        this->reservations[i].room_index = -1;
    }

}

// destrutor
ReservationSystem::~ReservationSystem(){
    delete[] this->room_capacities;
    delete[] this->reservations;
}

// IMPLEMENTAÇÃO ReservationRequest

bool ReservationSystem::reserve(ReservationRequest request){
    
    // checa a capacidade de cada sala, se não cabe a turma já passa pra próxima
    for(int i = 0; i < room_count; i++){
        if(room_capacities[i] < request.getStudentCount()){
            continue;
        }

        bool available = true;
        // se chegar aqui é porque tem capacidade

        // percorre cada reserva que seja no mesmo dia do pedido
        for(int j = 0; j < reservation_count; j++){
            if((reservations[j].room_index == i) && (reservations[j].weekday == request.getWeekday())){
                // vê se os horários vão bater nega os modos que não bate horário (Fim de B <= Início de A ou Início de B >= Fim de A)
                if (!((request.getStartHour() >= reservations[j].end_hour) || (request.getEndHour() <= reservations[j].start_hour))){
                    available = false; // diz que a sala tá indisponível
                    break; // para de checar essa sala
                }
            }
        }

        // se cabe os alunos e os horários não batem cria a reserva, aumenta o número de reservas e retorna true 
        if(available){
            reservations[reservation_count].course_name = request.getCourseName();
            reservations[reservation_count].weekday = request.getWeekday();
            reservations[reservation_count].start_hour = request.getStartHour();
            reservations[reservation_count].end_hour = request.getEndHour();
            reservations[reservation_count].room_index = i;
            reservation_count++;
            return true;
        }
    }
    // se nenhuma sala tem as características desejadas retorna false
    return false;
}


bool ReservationSystem::cancel(std::string course_name){
    // percorro as reservas
    // se nome do curso tem uma reserva tenho que remover da lista, como?
    // se não retorno false

    for(int i = 0 ; i < reservation_count; i++){
        if (reservations[i].course_name == course_name){
            // pega o último e coloca no lugar do que é pra ser removido
            reservations[i] = reservations[reservation_count - 1];
            // diminui o índice do último lugar
            reservation_count--;
            return true;
        }
    }
    return false;
}

void ReservationSystem::printSchedule(){

    std::string week = ["seg", "ter", "qua", "qui", "sex"];
    for(int i = 0; i < room_count; i++){
        std::cout <<"Room " << i << std::endl;
        for(int d = 0; d < 5; d++){
            for(int j = 0; j < reservation_count; j++){
            if((reservations[i].room_index == i) && (reservations[i].weekday == d)){
                // to na reserva j da sala i
                // printar o dia da semana
                // printar horários
            }
        }
        }
    }
}