#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

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

public:
    User() {
        // TODO: Implement default constructor
    }

    User(string uname, string pwd, string phone) {
        // TODO: Implement parameterized constructor
    }

    string getUsername() const {
        // TODO: Implement getter
        return "";
    }

    string getPhoneNumber() const {
        // TODO: Implement getter
        return "";
    }

    string getStatus() const {
        // TODO: Implement getter
        return "";
    }

    string getLastSeen() const {
        // TODO: Implement getter
        return "";
    }

    void setStatus(string newStatus) {
        // TODO: Implement setter
    }

    void setPhoneNumber(string phone) {
        // TODO: Implement setter
    }

    void updateLastSeen() {
        // TODO: Implement last seen update
    }

    bool checkPassword(string pwd) const {
        // TODO: Implement password check
        return false;
    }

    void changePassword(string newPwd) {
        // TODO: Implement password change
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
        // TODO: Implement default constructor
    }

    Message(string sndr, string cntnt) {
        // TODO: Implement parameterized constructor
    }

    string getContent() const {
        // TODO: Implement getter
        return "";
    }

    string getSender() const {
        // TODO: Implement getter
        return "";
    }

    string getTimestamp() const {
        // TODO: Implement getter
        return "";
    }

    string getStatus() const {
        // TODO: Implement getter
        return "";
    }

    Message* getReplyTo() const {
        // TODO: Implement getter
        return nullptr;
    }

    void setStatus(string newStatus) {
        // TODO: Implement setter
    }

    void setReplyTo(Message* msg) {
        // TODO: Implement setter
    }

    void updateTimestamp() {
        // TODO: Implement timestamp update
    }

    void display() const {
        // TODO: Implement message display
    }

    void addEmoji(string emojiCode) {
        // TODO: Implement emoji support
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
		chatName = name;
    }

    void addMessage(const Message& msg) {
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string& username) {
        if (index < 0 || index >= messages.size())
            return false;

        if (messages[index].getSender() != username)
            return false;

        messages.erase(messages.begin() + index);
        return true;
    }

    virtual void displayChat() const {
        cout << "Chat Name: " << chatName << endl;
        cout << "Participants: ";

        for (int i = 0; i < participants.size(); i++) {
            cout << participants[i];

            if (i != participants.size() - 1)
                cout << ", ";
        }
        cout << endl << endl;

        for (int i = 0; i < messages.size(); i++) {
            messages[i].display();
        }
    }

    vector<Message> searchMessages(string keyword) const {
        vector<Message> result;

        for (int i = 0; i < messages.size(); i++) {

            if (messages[i].getContent().find(keyword) != string::npos)
                result.push_back(messages[i]);
        }

        return result;
        
    }

    void exportToFile(const string& filename) const {
        // TODO: Implement export to file
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
        // TODO: Implement constructor
    }

    void displayChat() const override {
        // TODO: Implement private chat display
    }

    void showTypingIndicator(const string& username) const {
        // TODO: Implement typing indicator
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
    GroupChat(vector<string> users, string name, string creator): Chat(users, name){
        // TODO: Implement constructor
        admins.push_back(creator);
        if (!isParticipant(creator))
        {
            participants.push_back(creator);
        }
    }

    void addAdmin(string newAdmin) {
        // TODO: Implement add admin
        if(isParticipant(newAdmin) && !isAdmin(newAdmin))
        {
            admins.push_back(newAdmin);
		}

    }

    bool removeParticipant(const string& admin, const string& userToRemove) {
        // TODO: Implement remove participant

        if (isAdmin(admin))
        {
            if (isParticipant(userToRemove))
            {
                for (int i = 0; i < participants.size(); i++)
                {
                    if (participants[i] == userToRemove)
                    {
                        participants.erase(participants.begin() + i);
                        if (isAdmin(userToRemove))
                        {
                            for (int i = 0; i < admins.size(); i++)
                            {
                                if (admins[i] == userToRemove)
                                {
                                    admins.erase(admins.begin() + i);
                                }
                            }
                        }
                        return true;
                    }

                }
            }
        }
        return false;
    }

    bool isAdmin(string username) const {
        // TODO: Implement admin check
        for(int i=0; i < admins.size(); i++)
        {
            if (admins[i] == username)
            {
                return true;
            }
		}
        return false;
    }

    bool isParticipant(string username) const {
        // TODO: Implement participant check
        for (int i = 0; i < participants.size(); i++)
        {
            if (participants[i] == username)
            {
                return true;
            }
        }
        return false;
    }

    void setDescription(string desc) {
        // TODO: Implement set description
		description = desc;
    }

    void displayChat() const override {
        // TODO: Implement group chat display
		/*cout << "Group Name: " << chatName << endl;
		cout << "Description: " << description << endl;
        cout << "Admins:";
        for(int i=0; i<admins.size(); i++)
        {
            cout << admins[i] << " ";
		}
        cout<<"Messages:";
        for (int i = 0; i < messages.size(); i++)
        {
           messages[i].display();
        }*/
    }

    void sendJoinRequest(const string& username) {
        // TODO: Implement join request
        if(!isParticipant(username))
        {
            cout << username << "request to join" << endl;
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
        // TODO: Implement user search
        return -1;
    }

    bool isLoggedIn() const {
        // TODO: Implement login check
        return currentUserIndex != -1;
    }

    string getCurrentUsername() const {
        // TODO: Implement get current user
        return "";
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp() {
        // TODO: Implement user registration
    }

    void login() {
        // TODO: Implement user login
    }

    void startPrivateChat() {
        // TODO: Implement private chat creation

        string username;

        cout << "Enter username to start chatting with: ";
        cin >> username;

        if (findUserIndex(username) == -1) {
            cout << "User not found.\n";
            return;
        }

        if (username == getCurrentUsername()) {
            cout << "You cannot create a chat with yourself.\n";
            return;
        }

        Chat* newChat = new PrivateChat(getCurrentUsername(), username);
        chats.push_back(newChat);

        cout << "Private chat created successfully.\n";
    }

    void createGroup() {
        // TODO: Implement group creation

        string groupName;
        int numberOfParticipants;

        cout << "Enter group name: ";
        cin >> groupName;

        cout << "Enter number of participants: ";
        cin >> numberOfParticipants;

        if (numberOfParticipants < 2) {
            cout << "A group must have at least 2 participants.\n";
            return;
        }

        vector<string> participants;
        participants.push_back(getCurrentUsername());

        for (int i = 0; i < numberOfParticipants; i++) {
            string username;

            cout << "Enter participant " << i + 1 << ": ";
            cin >> username;

            if (findUserIndex(username) == -1) {
                cout << "User " << username << " does not exist.\n";
                continue;
            }

            participants.push_back(username);
        }

        Chat* newGroup = new GroupChat(participants, groupName, getCurrentUsername());
        chats.push_back(newGroup);

        cout << "Group created successfully.\n";
    }

    void viewChats() const {
        // TODO: Implement chat viewing

        if (chats.empty()) {
            cout << "No chats available.\n";
            return;
        }

        cout << "\n===== Chats =====\n";

        for (int i = 0; i < chats.size(); i++) {
            cout << "\nChat " << i + 1 << ":\n";
            chats[i]->displayChat();
        }
    }

    void logout() {
        // TODO: Implement logout
    }

    void run() {
        while (true) {
            if (!isLoggedIn()) {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";

                int choice;
                cin >> choice;

                if (choice == 1) {
                    login();
                }
                else if (choice == 2) {
                    signUp();
                }
                else if (choice == 3) {
                    cout << "Exiting WhatsApp...\n";
                    break;
                }
                else {
                    cout << "Invalid choice.\n";
                }
            }
            else {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";

                int choice;
                cin >> choice;

                if (choice == 1) {
                    startPrivateChat();
                }
                else if (choice == 2) {
                    createGroup();
                }
                else if (choice == 3) {
                    viewChats();
                }
                else if (choice == 4) {
                    logout();
                }
                else {
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
