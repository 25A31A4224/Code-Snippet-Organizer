#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Snippet {
private:
    std::string title;
    std::string description;
    std::string language;
    std::vector<std::string> tags;

public:
    Snippet(std::string t, std::string d, std::string lang, std::vector<std::string> tg)
        : title(t), description(d), language(lang), tags(tg) {}

    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }
    std::string getLanguage() const { return language; }
    std::vector<std::string> getTags() const { return tags; }

    void display() const {
        std::cout << "Title: " << title << "\n"
                  << "Language: " << language << "\n"
                  << "Description: " << description << "\n"
                  << "Tags: ";
        for (auto &tag : tags) std::cout << tag << " ";
        std::cout << "\n-----------------------------\n";
    }
};

class SnippetManager {
private:
    std::vector<Snippet> snippets;

public:
    void addSnippet(const Snippet& s) {
        snippets.push_back(s);
    }

    void listSnippets() const {
        if (snippets.empty()) {
            std::cout << "No snippets available.\n";
            return;
        }
        for (const auto& s : snippets) {
            s.display();
        }
    }

    void searchSnippet(const std::string& keyword) const {
        bool found = false;
        for (const auto& s : snippets) {
            if (s.getTitle().find(keyword) != std::string::npos ||
                s.getDescription().find(keyword) != std::string::npos ||
                s.getLanguage().find(keyword) != std::string::npos) {
                s.display();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No snippets found for keyword: " << keyword << "\n";
        }
    }
};

int main() {
    SnippetManager manager;

    // Demo snippets
    manager.addSnippet(Snippet("Binary Search", "Efficient search in sorted arrays", "C++", {"algorithm", "search"}));
    manager.addSnippet(Snippet("Hello World", "Basic program to print text", "C++", {"beginner", "intro"}));

    std::cout << "=== Code Snippet Organizer ===\n";
    std::cout << "Commands: add, list, search <keyword>, exit\n";

    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "list") {
            manager.listSnippets();
        } else if (command.rfind("search", 0) == 0) {
            std::string keyword = command.substr(7);
            manager.searchSnippet(keyword);
        } else if (command.rfind("add", 0) == 0) {
            std::string title, description, language, tagInput;
            std::cout << "Enter title: ";
            std::getline(std::cin, title);
            std::cout << "Enter description: ";
            std::getline(std::cin, description);
            std::cout << "Enter language: ";
            std::getline(std::cin, language);
            std::cout << "Enter tags (comma separated): ";
            std::getline(std::cin, tagInput);

            std::vector<std::string> tags;
            size_t pos = 0;
            while ((pos = tagInput.find(',')) != std::string::npos) {
                tags.push_back(tagInput.substr(0, pos));
                tagInput.erase(0, pos + 1);
            }
            if (!tagInput.empty()) tags.push_back(tagInput);

            manager.addSnippet(Snippet(title, description, language, tags));
            std::cout << "Snippet added successfully!\n";
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}
