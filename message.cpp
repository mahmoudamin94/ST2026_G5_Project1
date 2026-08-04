 #include <iostream>
 #include <string>
 #include <ctime>
 using namespace std;

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
        status = "";
        replyTo = nullptr;
    }

    Message(string sndr, string cntnt) {
        sender = sndr;
        content = cntnt;
        status = "sent";
        replyTo = nullptr;
        updateTimestamp();
    }

    string getContent() const {
        return content;
    }

    string getSender() const {
        return sender;
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
        time_t now = time(0);
        timestamp = ctime(&now);
    }

    void display() const {
        cout << "[" << timestamp << "] "
             << sender << ": "
             << content
             << " (" << status << ")" << endl;
    }

    void addEmoji(string emojiCode) {
        if (emojiCode == ":)") {
            size_t pos = content.find(":)");
            if (pos != string::npos)
                content.replace(pos, 2, "🙂");
        }
        else if (emojiCode == ":(") {
            size_t pos = content.find(":(");
            if (pos != string::npos)
                content.replace(pos, 2, "🙁");
        }
        else if (emojiCode == ":D") {
            size_t pos = content.find(":D");
            if (pos != string::npos)
                content.replace(pos, 2, "😃");
        }
        else if (emojiCode == "<3") {
            size_t pos = content.find("<3");
            if (pos != string::npos)
                content.replace(pos, 2, "❤️");
        }
    }
};