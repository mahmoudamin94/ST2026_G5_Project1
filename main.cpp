#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cctype>

using namespace std;

// ========================
//   HELPER: TRIM STRING
// ========================
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}
bool isAllDigits(const string& s) {
    if (s.empty())
        return false;

    for (char c : s) {
        if (!isdigit((unsigned char)c))
            return false;
    }

    return true;
}

// ========================
//       USER CLASS
// ========================
class User {
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

    string hashPassword(const string& pwd) const {
        unsigned long hash = 5381;

        for (size_t i = 0; i < pwd.length(); i++) {
            hash = ((hash << 5) + hash) + (unsigned char)pwd[i];
        }

        return to_string(hash);
    }

public:
    User() {
        username = "";
        password = "";
        phoneNumber = "";
        status = "offline";
        lastSeen = to_string(time(nullptr));
    }

    User(string uname, string pwd, string phone) {
        username = trim(uname);
        password = hashPassword(pwd);
        phoneNumber = trim(phone);
        status = "online";
        lastSeen = to_string(time(nullptr));
    }


    string getUsername() const {
        return username;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    string getStatus() const {
        return status;
    }

    string getLastSeen() const {
        return lastSeen;
    }


    void setStatus(string newStatus) {
        status = newStatus;
    }

    void setPhoneNumber(string phone) {
        phoneNumber = trim(phone);
    }


    void updateLastSeen() {
        lastSeen = to_string(time(nullptr));
    }

    bool checkPassword(string pwd) const {
        return password == hashPassword(pwd);
    }

    void changePassword(string newPwd) {
        if (newPwd.length() < 6) {
            cout << "Password must be at least 6 characters.\n";
            return;
        }

        password = hashPassword(newPwd);
    }
};
// ========================
//      MESSAGE CLASS
// ========================
class Message {
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message* replyTo;

public:
    Message() {
        sender = "";
        content = "";
        timestamp = "";
        status = "sent";
        replyTo = nullptr;
    }

    Message(string sndr, string cntnt) {
        sender = trim(sndr);
        content = trim(cntnt);
        status = "sent";
        replyTo = nullptr;
        updateTimestamp();
    }



    string getSender() const {
        return sender;
    }

    string getContent() const {
        return content;
    }

    string getTimestamp() const {
        return timestamp;
    }

    string getStatus() const {
        return status;
    }

    Message* getReplyTo() const {
        return replyTo;
    }



    void setStatus(string newStatus) {
        status = newStatus;
    }

    void setReplyTo(Message* msg) {
        replyTo = msg;
    }



    void updateTimestamp() {
        time_t now = time(nullptr);
        timestamp = ctime(&now);

        if (!timestamp.empty() && timestamp.back() == '\n')
            timestamp.pop_back();
    }

    void display() const {
        cout << "[" << timestamp << "] "
             << sender << ": "
             << content
             << " (" << status << ")";

        if (replyTo != nullptr) {
            cout << " [Reply to: " << replyTo->getSender() << "]";
        }

        cout << endl;
    }

    void addEmoji(string emojiCode) {
        size_t pos;

        if (emojiCode == ":)") {
            pos = content.find(":)");
            if (pos != string::npos)
                content.replace(pos, 2, "\xF0\x9F\x99\x82"); // 🙂
        }
        else if (emojiCode == ":(") {
            pos = content.find(":(");
            if (pos != string::npos)
                content.replace(pos, 2, "\xF0\x9F\x99\x81"); // 🙁
        }
        else if (emojiCode == ":D") {
            pos = content.find(":D");
            if (pos != string::npos)
                content.replace(pos, 2, "\xF0\x9F\x98\x83"); // 😃
        }
        else if (emojiCode == "<3") {
            pos = content.find("<3");
            if (pos != string::npos)
                content.replace(pos, 2, "\xE2\x9D\xA4\xEF\xB8\x8F"); // ❤️
        }
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat {
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat() {
        participants.clear();
        messages.clear();
        chatName = "";
    }

    Chat(vector<string> users, string name) {
        participants = users;
        chatName = trim(name);
    }

    virtual ~Chat() {}



    string getChatName() const {
        return chatName;
    }

    const vector<string>& getParticipants() const {
        return participants;
    }

    const vector<Message>& getMessages() const {
        return messages;
    }



    bool isParticipant(const string& username) const {
        for (size_t i = 0; i < participants.size(); i++) {
            if (participants[i] == username)
                return true;
        }
        return false;
    }


    void addMessage(const Message& msg) {
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string& username) {
        if (index < 0 || index >= (int)messages.size())
            return false;

        if (messages[index].getSender() != username)
            return false;

        messages.erase(messages.begin() + index);
        return true;
    }

    vector<Message> searchMessages(const string& keyword) const {
        vector<Message> result;

        for (size_t i = 0; i < messages.size(); i++) {
            if (messages[i].getContent().find(keyword) != string::npos)
                result.push_back(messages[i]);
        }

        return result;
    }


    virtual void displayChat() const {
        cout << "Chat Name: " << chatName << endl;

        cout << "Participants: ";

        for (size_t i = 0; i < participants.size(); i++) {
            cout << participants[i];

            if (i != participants.size() - 1)
                cout << ", ";
        }

        cout << "\n\nMessages:\n";

        if (messages.empty()) {
            cout << "No messages yet.\n";
            return;
        }

        for (size_t i = 0; i < messages.size(); i++) {
            cout << i + 1 << ". ";
            messages[i].display();
        }
    }

    void exportToFile(const string& filename) const {
        // TODO
    }
};


// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat {
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2) {
        user1 = trim(u1);
        user2 = trim(u2);

        participants.push_back(user1);
        participants.push_back(user2);

        chatName = "Chat between " + user1 + " and " + user2;
    }

    void displayChat() const override {
        cout << "===== " << chatName << " =====\n";

        if (messages.empty()) {
            cout << "No messages yet.\n";
            return;
        }

        for (size_t i = 0; i < messages.size(); i++) {
            cout << i + 1 << ". ";
            messages[i].display();
        }
    }

    void showTypingIndicator(const string& username) const {
        if (username == user1 || username == user2) {
            cout << username << " is typing...\n";
        }
    }

    string getFirstUser() const {
        return user1;
    }

    string getSecondUser() const {
        return user2;
    }
};


// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat {
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator)
        : Chat(users, trim(name)) {

        if (!isParticipant(creator))
            participants.push_back(trim(creator));

        admins.push_back(trim(creator));
        description = "";
    }
    bool addParticipant(const string& username) {

        if (isParticipant(username)) {
            cout << "User is already in the group.\n";
            return false;
        }

        participants.push_back(username);
        return true;
    }

    bool isAdmin(const string& username) const {
        for (size_t i = 0; i < admins.size(); i++) {
            if (admins[i] == username)
                return true;
        }
        return false;
    }

    void addAdmin(const string& newAdmin) {
        if (!isParticipant(newAdmin)) {
            cout << "User is not a participant.\n";
            return;
        }

        if (isAdmin(newAdmin)) {
            cout << "User is already an admin.\n";
            return;
        }

        admins.push_back(newAdmin);
        cout << newAdmin << " is now an admin.\n";
    }


    bool removeParticipant(const string& admin,
                           const string& userToRemove) {

        if (!isAdmin(admin))
            return false;

        if (!isParticipant(userToRemove))
            return false;

        if (admin == userToRemove)
            return false;

        for (size_t i = 0; i < participants.size(); i++) {

            if (participants[i] == userToRemove) {

                participants.erase(participants.begin() + i);

                for (size_t j = 0; j < admins.size(); j++) {

                    if (admins[j] == userToRemove) {

                        admins.erase(admins.begin() + j);
                        break;
                    }
                }

                return true;
            }
        }

        return false;
    }


    void setDescription(const string& desc) {
        description = trim(desc);
    }

    string getDescription() const {
        return description;
    }


    void sendJoinRequest(const string& username) {

        if (isParticipant(username)) {
            cout << username << " is already in the group.\n";
            return;
        }

        cout << username << " requested to join the group.\n";
    }


    void displayChat() const override {

        cout << "===== " << chatName << " =====\n";

        cout << "Description: ";

        if (description.empty())
            cout << "(none)";
        else
            cout << description;

        cout << "\n\nAdmins: ";

        for (size_t i = 0; i < admins.size(); i++) {

            cout << admins[i];

            if (i != admins.size() - 1)
                cout << ", ";
        }

        cout << "\nParticipants: ";

        for (size_t i = 0; i < participants.size(); i++) {

            cout << participants[i];

            if (i != participants.size() - 1)
                cout << ", ";
        }

        cout << "\n\nMessages:\n";

        if (messages.empty()) {
            cout << "No messages yet.\n";
            return;
        }

        for (size_t i = 0; i < messages.size(); i++) {
            cout << i + 1 << ". ";
            messages[i].display();
        }
    }
};
// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp {
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;

    int findUserIndex(string username) const {
        username = trim(username);
        for (size_t i = 0; i < users.size(); i++) {
            if (users[i].getUsername() == username)
                return (int)i;
        }
        return -1;
    }

    bool isLoggedIn() const {
        return currentUserIndex != -1;
    }

    string getCurrentUsername() const {
        if (!isLoggedIn())
            return "";
        return users[currentUserIndex].getUsername();
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    ~WhatsApp() {
        for (size_t i = 0; i < chats.size(); i++) {
            delete chats[i];
        }
    }

void signUp() {
    string username;
    string password;
    string phoneNumber;

    // Username
    cout << "Enter username: ";
    cin >> username;
    username = trim(username);

    if (username.empty()) {
        cout << "Username cannot be empty.\n";
        return;
    }

    if (findUserIndex(username) != -1) {
        cout << "Username already exists!\n";
        return;
    }

    // Password
    cout << "Enter password: ";
    cin >> password;

    if (password.length() < 6) {
        cout << "Password must be at least 6 characters.\n";
        return;
    }

    // Phone Number
    while (true) {
        cout << "Enter phone number: ";
        cin >> phoneNumber;
        phoneNumber = trim(phoneNumber);

        if (!isAllDigits(phoneNumber)) {
            cout << "Phone number must contain digits only.\n";
            continue;
        }

        if (phoneNumber.length() != 11) {
            cout << "Phone number must contain exactly 11 digits.\n";
            continue;
        }

        bool exists = false;
        for (size_t i = 0; i < users.size(); i++) {
            if (users[i].getPhoneNumber() == phoneNumber) {
                exists = true;
                break;
            }
        }

        if (exists) {
            cout << "Phone number already registered.\n";
            continue;
        }

        break;
    }

    users.push_back(User(username, password, phoneNumber));

    cout << "Registration Successful!\n";
}

    void login() {
        string username;
        cout << "Enter username: ";
        cin >> username;
        username = trim(username);

        int index = findUserIndex(username);
        if (index == -1) {
            cout << "Invalid username!\n";
            return;
        }

        string password;
        cout << "Enter password: ";
        cin >> password;

        if (users[index].checkPassword(password)) {
            currentUserIndex = index;
            cout << "Login Successful!\n";
            users[index].setStatus("online");
            users[index].updateLastSeen();
        }
        else {
            cout << "Incorrect password!\n";
        }
    }

    void startPrivateChat() {
        string username;

        cout << "Enter username to start chatting with: ";
        cin >> username;
        username = trim(username);

        if (findUserIndex(username) == -1) {
            cout << "User not found.\n";
            return;
        }

        if (username == getCurrentUsername()) {
            cout << "You cannot create a chat with yourself.\n";
            return;
        }
        for (size_t i = 0; i < chats.size(); i++) {
            if (chats[i]->isParticipant(getCurrentUsername()) &&
                chats[i]->isParticipant(username)) {
                cout << "Private chat already exists.\n";
                return;
            }
        }
        Chat* newChat = new PrivateChat(getCurrentUsername(), username);
        chats.push_back(newChat);

        cout << "Private chat created successfully.\n";
    }

    //Delete message wrapper
    void deleteMessage() {
    if (chats.empty()) {
        cout << "No chats available.\n";
        return;
    }

    viewChats();

    int chatChoice;
    cout << "Select chat: ";
    cin >> chatChoice;

    if (chatChoice < 1 || chatChoice > chats.size()) {
        cout << "Invalid chat.\n";
        return;
    }

    chats[chatChoice - 1]->displayChat();

    int messageIndex;
    cout << "Enter message number: ";
    cin >> messageIndex;

    if (chats[chatChoice - 1]->deleteMessage(messageIndex - 1,
                                             getCurrentUsername()))
        cout << "Message deleted.\n";
    else
        cout << "Cannot delete this message.\n";
}

// Search message wrapper

void searchMessages() {
    string keyword;

    cin.ignore();

    cout << "Keyword: ";
    getline(cin, keyword);

    bool found = false;

    for (size_t i = 0; i < chats.size(); i++) {

        vector<Message> result =
            chats[i]->searchMessages(keyword);

        if (!result.empty()) {

            cout << "\nIn "
                 << chats[i]->getChatName()
                 << endl;

            for (size_t j = 0; j < result.size(); j++)
                result[j].display();

            found = true;
        }
    }

    if (!found)
        cout << "No messages found.\n";
}

// remove participant wrapper

void removeParticipant() {

    vector<GroupChat*> groups;

    for (size_t i = 0; i < chats.size(); i++) {

        GroupChat* group =
            dynamic_cast<GroupChat*>(chats[i]);

        if (group != nullptr)
            groups.push_back(group);
    }

    if (groups.empty()) {
        cout << "No groups found.\n";
        return;
    }

    for (size_t i = 0; i < groups.size(); i++)
        cout << i + 1 << ". "
             << groups[i]->getChatName()
             << endl;

    int choice;
    cin >> choice;

    if (choice < 1 || choice > groups.size())
        return;

    string username;

    cout << "Username: ";
    cin >> username;

    if (username == getCurrentUsername()) {
        cout << "You cannot remove yourself.\n";
        return;
    }

    if (groups[choice - 1]->removeParticipant(
            getCurrentUsername(),
            username))
        cout << "Participant removed.\n";
    else
        cout << "Failed.\n";
}


void addParticipant() {

    vector<GroupChat*> groups;


    // Get all groups
    for (size_t i = 0; i < chats.size(); i++) {

        GroupChat* group = dynamic_cast<GroupChat*>(chats[i]);

        if (group != nullptr)
            groups.push_back(group);
    }


    if (groups.empty()) {
        cout << "No groups found.\n";
        return;
    }


    // Display groups
    cout << "\n===== Groups =====\n";

    for (size_t i = 0; i < groups.size(); i++) {
        cout << i + 1 << ". "
             << groups[i]->getChatName()
             << endl;
    }


    int choice;

    cout << "Select group: ";
    cin >> choice;


    if (choice < 1 || choice > (int)groups.size()) {
        cout << "Invalid group.\n";
        return;
    }


    string username;

    cout << "Enter username to add: ";
    cin >> username;

    username = trim(username);


    // Check user exists
    if (findUserIndex(username) == -1) {
        cout << "User does not exist.\n";
        return;
    }


    if (groups[choice - 1]->addParticipant(username)) {
        cout << username << " added successfully.\n";
    }
}
  void createGroup() {
    string groupName;
    string description;
    int numberOfParticipants;

    cin.ignore(10000, '\n');

    cout << "Enter group name: ";
    getline(cin, groupName);
    groupName = trim(groupName);

    if (groupName.empty()) {
        cout << "Group name cannot be empty.\n";
        return;
    }


    cout << "Enter group description: ";
    getline(cin, description);
    description = trim(description);


    cout << "Enter number of participants to invite (not counting you): ";

    if (!(cin >> numberOfParticipants)) {
        cout << "Invalid number.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }


    if (numberOfParticipants < 1) {
        cout << "You must invite at least 1 other participant. Group not created.\n";
        return;
    }


    vector<string> participants;
    participants.push_back(getCurrentUsername());


    for (int i = 0; i < numberOfParticipants; i++) {

        string username;

        cout << "Enter participant " << i + 1 << ": ";

        cin >> username;
        username = trim(username);


        if (findUserIndex(username) == -1) {
            cout << "User \"" << username << "\" does not exist. Skipped.\n";
            continue;
        }


        if (username == getCurrentUsername()) {
            cout << "You're the creator, no need to add yourself.\n";
            continue;
        }


        bool alreadyAdded = false;

        for (size_t j = 0; j < participants.size(); j++) {

            if (participants[j] == username) {
                alreadyAdded = true;
                break;
            }
        }


        if (alreadyAdded) {
            cout << username << " is already in the group.\n";
            continue;
        }


        participants.push_back(username);
    }


    if (participants.size() < 2) {
        cout << "A group must have at least 2 participants (including you). "
             << "Group not created.\n";
        return;
    }


    GroupChat* group = new GroupChat(
        participants,
        groupName,
        getCurrentUsername()
    );

    group->setDescription(description);

    chats.push_back(group);

    cout << "Group created successfully.\n";
}

void sendMessage() {
    if (chats.empty()) {
        cout << "No chats available. Start a private chat or create a group first.\n";
        return;
    }

    cout << "\n===== Your Chats =====\n";
    for (size_t i = 0; i < chats.size(); i++) {
        cout << i + 1 << ". " << chats[i]->getChatName() << endl;
    }

    cout << "Select chat number to send a message to: ";

    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input.\n";
        return;
    }

    if (choice < 1 || choice > (int)chats.size()) {
        cout << "Invalid chat number.\n";
        return;
    }

    Chat* selectedChat = chats[choice - 1];

    if (!selectedChat->isParticipant(getCurrentUsername())) {
        cout << "You are not a participant of this chat.\n";
        return;
    }

    cin.ignore(10000, '\n');

    cout << "Enter your message: ";
    string content;
    getline(cin, content);

    if (trim(content).empty()) {
        cout << "Message cannot be empty.\n";
        return;
    }

    Message msg(getCurrentUsername(), content);

    msg.addEmoji(":)");
    msg.addEmoji(":(");
    msg.addEmoji(":D");
    msg.addEmoji("<3");

    selectedChat->addMessage(msg);

    cout << "Message sent!\n";
}
    void viewChats() const {
        if (chats.empty()) {
            cout << "No chats available.\n";
            return;
        }

        cout << "\n===== Chats =====\n";

        for (size_t i = 0; i < chats.size(); i++) {
            cout << "\nChat " << i + 1 << ":\n";
            chats[i]->displayChat();
        }
    }

   void logout() {
    if (!isLoggedIn()) {
        cout << "No user is currently logged in.\n";
        return;
    }

    users[currentUserIndex].setStatus("offline");
    users[currentUserIndex].updateLastSeen();

    currentUserIndex = -1;

    cout << "Logged out successfully!\n";
}

void run() {
    while (true) {

        if (!isLoggedIn()) {


            cout << "1. Login\n";
            cout << "2. Sign Up\n";
            cout << "3. Exit\n";
            cout << "Choice: ";

            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                login();
                break;

            case 2:
                signUp();
                break;

            case 3:
                cout << "Thank you for using WhatsApp!\n";
                return;

            default:
                cout << "Invalid choice.\n";
            }
        }
        else {

            cout << "\n===== Main Menu =====\n";
            cout << "1. Start Private Chat\n";
            cout << "2. Create Group\n";
            cout << "3. View Chats\n";
            cout << "4. Send Message\n";
            cout << "5. Delete Message\n";
            cout << "6. Search Messages\n";
            cout << "7. Remove Participant\n";
            cout << "8. Add Participant\n";
            cout << "9. Logout\n";
            cout << "Choice: ";

            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                startPrivateChat();
                break;

            case 2:
                createGroup();
                break;

            case 3:
                viewChats();
                break;

            case 4:
                sendMessage();
                break;

            case 5:
                deleteMessage();
                break;

            case 6:
                searchMessages();
                break;

            case 7:
                removeParticipant();
                break;

            case 8:
               addParticipant();
               break;

            case 9:
                logout();
                break;

            default:
                cout << "Invalid choice.\n";
            }
        }
    }
}
};

// ========================
//          MAIN
// ========================
int main() {
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
