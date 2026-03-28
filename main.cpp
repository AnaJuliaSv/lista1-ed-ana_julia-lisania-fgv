#include <iostream>
#include <algorithm>
#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"


// Funções
void doing_reserve(ReservationSystem& sys, ReservationRequest* requests, int tam_request){
    
    for (int i = 0; i <= tam_request; i++){
        bool avaiable = sys.reserve(requests[i]);

        if(avaiable){
            std::cout << "Reserva " << requests[i].getCourseName() << " " << requests[i].getWeekday() << 
            " realizada com sucesso." << std::endl;
        } else {
            std::cout << "A reserva " << requests[i].getCourseName() << " " << requests[i].getWeekday() << 
            " nao pode ser realizada por falta de disponibilidade." << std::endl;
        }

    }

    std::cout << " " << std::endl;
}


void doing_cancel(ReservationSystem& sys, ReservationRequest* requests, int tam){

    for (int i = 0; i < tam; i++){
        std::string name_course = requests[i].getCourseName();
        bool status_cancel = sys.cancel(requests[i].getCourseName());

        if(status_cancel){
            std::cout << "Cancelamento da reserva de " << name_course << " realizada com sucesso." << std::endl;
        } else {
            std::cout << "Cancelamento da reserva de " << name_course << " nao pode ser realizada." << std::endl;
            std::cout << "Disciplina " << name_course << " nao encontrada." << std::endl;
        }
    }

    std::cout << " " << std::endl;

}



int main(void){

    int rooms = 5;
    int capacities[5] = {60, 40, 40, 35, 50};

    // Criando o sistema
    ReservationSystem reservation_system(rooms, capacities);

    std::cout << "Reservas: " << std::endl;
    std::cout << " " << std::endl;

    // Criando os objetos para reserva
    // Casos que darão certo
    ReservationRequest request_1("Geometria Analitica", "segunda", 7, 9, 50);
    ReservationRequest request_2("Fisica I", "segunda", 9, 11, 40);
    ReservationRequest request_3("Sociologia II", "terca", 15, 18, 50);
    ReservationRequest request_4("Geometria Analitica", "terca", 7, 9, 50);
    ReservationRequest request_5("Quimica I", "terca", 11, 13, 35);
    ReservationRequest request_6("Fisica I", "terca", 11, 14, 40);
    ReservationRequest request_7("Filosofia III", "terca", 18, 21, 60);
    ReservationRequest request_8("Geometria Analitica", "quarta", 7, 9, 50);
    ReservationRequest request_9("TACD", "quarta", 7, 9, 50);
    ReservationRequest request_10("Quimica I", "quarta", 13, 16, 50);
    ReservationRequest request_11("Quimica I", "segunda", 14, 16, 60);

    // Casos de reserva sem disponibilidade
    ReservationRequest request_12("Calculo II", "terca", 18, 21, 60);
    ReservationRequest request_13("Calculo II", "segunda", 7, 11, 55);


    // Criando um array de reservas
    ReservationRequest requests[13] = {request_1, request_2, request_3, request_4, request_5, request_6,
                                        request_7, request_8, request_9, request_10, request_11, request_12, request_13};

    // Criando as reservas
    doing_reserve(reservation_system, requests, 12);

    
    std::cout << "Cancelamentos: " << std::endl;
    std::cout << " " << std::endl;

    // Cancelando a reserva de request_1 : Geometria Analitica, e request_3: Sociologia
    ReservationRequest cancel_request[2] = {request_1, request_3};
    doing_cancel(reservation_system, cancel_request, 2); 


    
    std::cout << "Grade Final: " << std::endl;

    // Exibição da grade de horários
    reservation_system.printSchedule();

}
