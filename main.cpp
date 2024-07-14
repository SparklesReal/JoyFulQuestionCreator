#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filereadstream.h>
#include <fstream>
#include <iostream>

int main() {
    int option = 0;
    bool running = true;
    rapidjson::Document document;

    std::cout << "Welcome to JoyfulQuestionCreator!\n";
    std::cout << "New questions.json file (1), Append to questions.json file (2)\n";
    std::cin >> option;

    if (option == 1 || option == 2) {
        if (option == 2) {
            FILE* fp = fopen("questions.json", "r");
            if (!fp) {
                std::cerr << "Error opening file" << std::endl;
                return 1;
            }

            char readBuffer[65536];
            rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

            document.ParseStream(is);
            fclose(fp);

            if (document.HasParseError()) {
                std::cerr << "Error parsing JSON" << std::endl;
                return 1;
            }
        }

        if (option == 1) {
            document.SetObject();
            rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
            document.AddMember("questions", rapidjson::Value(rapidjson::kArrayType), allocator);
        }
    } else {
        return 1;
    }

    std::string title = "";
    std::string answer1 = "";
    std::string answer2 = "";
    std::string answer3 = "";
    std::string answer4 = "";
    int correctAnswer = 0;

    while (running) {
        std::cout << "Enter question title (enter 'q' to quit and save)\n";
        std::getline(std::cin >> std::ws, title);
        if (title == "q") {
            running = false;
            break;
        }
        std::cout << "Enter question answer1\n";
        std::getline(std::cin >> std::ws, answer1);
        std::cout << "Enter question answer2\n";
        std::getline(std::cin >> std::ws, answer2);
        std::cout << "Enter question answer3\n";
        std::getline(std::cin >> std::ws, answer3);
        std::cout << "Enter question answer4\n";
        std::getline(std::cin >> std::ws, answer4);
        std::cout << "Enter correct answer (1-4)\n";
        std::cin >> correctAnswer;

        if (correctAnswer < 1 || correctAnswer > 4) {
            std::cerr << "Invalid correct answer. Please enter a number between 1 and 4.\n";
            return 1;
        }

        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value newQuestion(rapidjson::kObjectType);
        newQuestion.AddMember("title", rapidjson::Value(title.c_str(), allocator).Move(), allocator);
        newQuestion.AddMember("answer1", rapidjson::Value(answer1.c_str(), allocator).Move(), allocator);
        newQuestion.AddMember("answer2", rapidjson::Value(answer2.c_str(), allocator).Move(), allocator);
        newQuestion.AddMember("answer3", rapidjson::Value(answer3.c_str(), allocator).Move(), allocator);
        newQuestion.AddMember("answer4", rapidjson::Value(answer4.c_str(), allocator).Move(), allocator);
        newQuestion.AddMember("correctAnswer", correctAnswer, allocator);

        document["questions"].PushBack(newQuestion, allocator);
    }

    std::ofstream ofs("questions.json");
    if (!ofs.is_open()) {
        std::cerr << "Error opening file for writing" << std::endl;
        return 1;
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    ofs << buffer.GetString() << std::endl;

    ofs.close();

    return 0;
}