#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"

// Construtor
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

// Destrutor
ReservationSystem::~ReservationSystem(){
    delete[] this->room_capacities;
    delete[] this->reservations;
}

// Métodos ReservationSystem

bool ReservationSystem::reserve(ReservationRequest request){
    
    // Verifica a capacidade de cada sala, se não cabe a turma já passa pra próxima
    for(int i = 0; i < room_count; i++){
        if(room_capacities[i] < request.getStudentCount()){
            continue;
        }

        // Se tiver capacidade, a variável avaible é true
        bool available = true;
        

        // Percarre cada reserva que seja no mesmo dia do pedido
        for(int j = 0; j < reservation_count; j++){
            if((reservations[j].room_index == i) && (reservations[j].weekday == request.getWeekday())){

                // Verifica se os horários vão bater, negando os modos que não bate horário (Fim de B <= Início de A ou Início de B >= Fim de A)
                if (!((request.getStartHour() >= reservations[j].end_hour) || (request.getEndHour() <= reservations[j].start_hour))){
                    available = false; 
                    break; // Para de checar essa sala
                }
            }
        }

        // Se a sala comportar os alunos e os horários não colidirem, cria a reserva, 
        // aumenta o número de reservas e retorna true 
        if(available){
            this -> reservations[reservation_count].course_name = request.getCourseName();
            this -> reservations[reservation_count].weekday = request.getWeekday();
            this -> reservations[reservation_count].start_hour = request.getStartHour();
            this -> reservations[reservation_count].end_hour = request.getEndHour();
            this -> reservations[reservation_count].room_index = i;
            this -> reservation_count++;
            return true;
        }
    }
    // Se nenhuma sala tem as características desejadas retorna false
    return false;
}


bool ReservationSystem::cancel(std::string course_name){
    // Percorre as reservas

    for(int i = 0 ; i < reservation_count; i++){
        // Localiza a reserva desejada
        if (reservations[i].course_name == course_name){
            // Busca o último elemento e coloca no lugar do que será removido
            reservations[i] = reservations[reservation_count - 1];

            // Diminui o índice 
            reservation_count--;
            return true;
        }
    }

    // Se a reserva não existir, retorna false
    return false;
}


void ReservationSystem::printSchedule(){

    std::string week[] = {"segunda", "terca", "quarta", "quinta", "sexta"};

    // Percorrendo as salas disponíveis
    for (int j = 0; j < room_count; j++){
        bool room_reserved = false;

        // Verifica se existe alguma reserva pra a sala de index j
        for (int i = 0; i < reservation_count; i ++){
            if(reservations[i].room_index == j){
                room_reserved = true;
                break;
            }
        }

        // Se não houver, vai para a próxima sala j++
        if(!room_reserved){
            continue;
        }

        // Printando a sala reservada do loop atual
        std::string room = "Room " + std::to_string(j);
        std::cout << " " << std::endl;
        std::cout << room << std::endl;

        // Dado um dia da semana (em ordem)
        for (int d = 0; d < 5; d++){
            bool day_reserved = false;

            // Verifica se existe uma reserva para a sala j no dia d
            for (int i = 0; i < reservation_count; i++){
                if (reservations[i].room_index == j && reservations[i].weekday == week[d]){
                    day_reserved = true;
                    break;
                }
            }

            // Se não houver reservas no dia, passa para o próximo dia
            if(!day_reserved){
                continue;
            }

            // Se houver reservas na sala j neste dia, printa o dia
            std::cout << week[d] + ":" << std::endl; 

            // Buscando com base no horário da aula
            for (int time = 7; time < 22; time++){

                // Busca as reservas feitas para esse dia na sala do loop atual
                for (int i = 0; i < reservation_count; i++ ){

                    // Se for a sala, no dia e na hora em que buscamos, printa o time schedule da aula
                    if (reservations[i].room_index == j && reservations[i].weekday == week[d] && reservations[i].start_hour == time){       
                        int start = reservations[i].start_hour;
                        int ends = reservations[i].end_hour;
                        std::string duration = std::to_string(start) + "h~" + std::to_string(ends) + "h :";
        
                        std::string course = reservations[i].course_name;
                        std::string time_schedule = duration + course;

                        std::cout << time_schedule << std::endl;
                    }

                }

            }
      
            std::cout << " " << std::endl;
            
        }

    }

}
