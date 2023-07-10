

//builderTest.cpp


#include "Notification.h"


int main(){
    Notification notification = Notification::create()
            .setSmallIcon(1)
            .setContentTitle("Justin Rhyss")
            .setContentText("Do you want to go see a movie tonight?")
            .setPriority(5);
    std::cout << notification << std::endl;
}