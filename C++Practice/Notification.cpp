//
// Created by 이철용 on 2022/07/06.
//

#include "Notification.h"

std::ostream& operator << (std::ostream& os, const Notification& n){
    os << n.icon << " " << n.appName << " " ;
    int diff = (int)std::difftime(std::time(nullptr), n.timestamp) / (60 * 60 * 24);
    os <<  ((diff==0) ? "now" : std::to_string(diff) );
    os << ((diff==0) ? "" : " days" ) << std::endl;
    os << n.title << std::endl;
    os << n.text << std::endl;
    return os;
}
NotificationBuilder Notification::create(){
    // your code here
    auto i = std::unique_ptr <NotificationBuilder> (new NotificationBuilder);





}

NotificationBuilder& NotificationBuilder::setSmallIcon(int icon) {
    // your code here

    (this ->notification).icon = icon;

}

NotificationBuilder& NotificationBuilder::setContentTitle(std::string title) {
    // your code here
    (this->notification).title = title;
}

NotificationBuilder& NotificationBuilder::setContentText(std::string text) {
    // your code here
    (this->notification).text = text;
}

NotificationBuilder& NotificationBuilder::setPriority(int priority) {
    // your code here
    (this->notification).priority = priority;
}


