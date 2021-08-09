#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
std::string entity_names = "entity_names.txt";
std::ofstream names(entity_names,std::ios::app);

class ClassEntity {
public:
    ~ClassEntity() {
        names.close();
    }
    void Orders() {
        char c;
        
        std::cout << "do you want to know orders?[y/n]   ";
        std::cin >> c;
        if (c == 'y') {
            std::cout << "-> print [entyty name]\n";
            std::cout << "-> print [entyty name] : [KEY]\n";
            std::cout << "-> create [entity name] \n\t[KEY/name] type\n\t[name] type\n\t...\n\tall\n";
            std::cout << "-> insert [entity name] \n\t[KEY/name] : type\n\t[name] : type\n\t...\n\tall\n";
            std::cout << "-> update [entity name] : [KEY]\n\t[name] value \n\t...\n\tall\n";
            std::cout << "-> delete [entity name] : [KEY]\n";
        }
        if (c == 'n' || c == 'y') {
            std::string str, str1;
            std::cout << "(for exit input exit, for stop add variables input all)\n\n";
            while (true)
            {
                std::cout << "-> ";
                std::cin >> str;
                if (str == "exit") {
                    return;
                }
                if (str == "create") {
                    std::getline(std::cin, str1);
                    Create(str1);
                }
                else if (str == "insert") {
                    std::getline(std::cin, str1);
                    Insert(str1);
                }
                else if (str == "update") {
                    std::getline(std::cin, str1);
                    Update(str1);
                }
                else if (str == "delete") {
                    std::getline(std::cin, str1);
                    Delete(str1);
                }
                else if (str == "print") {
                    std::getline(std::cin, str1);
                    Print(str1);
                }
                else {
                    std::cout << "wrong order\n";
                }
            }
        }
        else {
            return;
        }
    }
    void Print(std::string& string) {
        std::stringstream s(string);
        std::string name, txt, tmp;
        s >> name;

        if (!find(name))
        {
            std::cout << "wrong entity name\n";
            return;
        }
        s >> txt;
        if (txt == ":") {
            s >> txt;
            if (!suitsNames(name, txt)) {
                std::cout << "there is no key like that\n";
                return;
            }
            getText(name, txt, tmp);
            tmp.erase(tmp.size() - 2, 1);
            std::cout << tmp << '\n';
        }
        else if (txt == "") {
            std::ifstream fst(name + ".txt");
            while (!fst.eof())
            {
                std::getline(fst, txt);
                if (txt == "") {
                    return;
                }
                txt.erase(txt.size() - 2, 1);
                std::cout << txt << '\n';
            }
        }
        else {
            std::cout << "wrong syntax\n";
        }
    }
    void Delete(std::string& string) {
        std::stringstream stream, stream_types;
        stream << string;
        std::string name1, name;
        stream >> name1;
        if (find(name1) == false) {
            std::cout << "there is no entity name like that\n";
            return;
        }
        stream >> name;
        if (name != ":") {
            std::cout << "wrong syntax\n";
            return;
        }
        stream >> name;
        if (!suitsNames(name1, name))
        {
            std::cout << "wrong key\n";
            return;
        }

        std::string cur;
        std::string types = getTypes(name1);
        std::string get = getText(name1, name, cur);

        std::ofstream ostr(name1 + ".txt");
        ostr.clear();
        ostr << get;
        ostr.close();
    }
    void Update(std::string& string) {
        std::stringstream stream, stream_types;
        stream << string;
        std::string name1, name;
        stream >> name1;
        if (find(name1) == false) {
            std::cout << "there is no entity name like that\n";
            return;
        }
        stream >> name;
        if (name != ":") {
            std::cout << "wrong syntax\n";
            return;
        }
        stream >> name;
        if (!suitsNames(name1, name))
        {
            std::cout << "wrong key\n";
            return;
        }

        std::string new_t, cur;
        std::string types = getTypes(name1);
        std::string get = getText(name1, name, cur);


        std::stringstream curS(cur), typesS(types);
        std::string curTmp, typesTmp, txt;
        typesS >> typesTmp;
        bool t = true;
        while (typesS >> typesTmp)
        {
            curS >> curTmp;
            std::cout << "\n\t" << typesTmp << " : ";
            std::cin >> txt;
            if (txt == "SKIP") {
                new_t += curTmp;
                typesS >> typesTmp;
            }
            else {
                if (t && suitsNames(name1, txt)) {
                    std::cout << "this key is already exis\n";
                    return;
                }
                typesS >> typesTmp;
                if (typesTmp == "int") {
                    for (int i = 0; i < txt.size(); i++)
                    {
                        if (txt[i] < 48 || txt[i]>57) {
                            std::cout << "your tipe should be int\n";
                            return;
                        }
                    }
                }
                new_t += txt;
            }
            new_t += "  ,  ";
            curS >> curTmp;
            typesS >> typesTmp;
            t = false;
        }
        std::ofstream ostr(name1 + ".txt");
        ostr.clear();
        ostr << get << new_t << '\n';
        ostr.close();
    }
    void Insert(std::string& name) {
        name.erase(0, 1);
        bool tr = false;
        std::string s, s2;
        std::stringstream stre;
        std::vector<std::string> values;
        stre << s;
        stre >> s2;
        std::ifstream istr(entity_names);
        while (!istr.eof() && !tr) {
            s2 = "";
            std::getline(istr, s);
            for (int i = 0; (i < s.size()) && !tr; i++)
            {
                if (s[i] == '\t' || s[i] == '\n' || s[i] == ' ') {
                    if (s2 != name) {
                        break;
                    }
                    else {
                        tr = true;
                    }
                }
                s2 += s[i];
            }
        }
        istr.close();
        if (!tr) {
            std::cout << "thre is no entity name like that\n";
            return;
        }
        int i = 0;
        std::stringstream str1;
        str1 << s;
        str1 >> s2;
        std::string name1 = s2;
        bool t = false;
        while (str1 >> s2) {
            std::string value;
            std::cout << "\n\t" << s2 << " : ";
            
            if (!t) {
                std::cin >> value;
                t = true;
                if (suitsNames(name1, value) == true) {
                    std::cout << "there is already exist key like that\n";
                    return;
                }
            }
            else {
                std::cin >> value;
                std::string h;
                std::getline(std::cin, h);
                value += h;
            }
            str1 >> s2;
            if (s2 == "int") {
                for (int i = 0; i < value.size(); i++)
                {
                    if (value[i] < 48 || value[i]>57) {
                        std::cout << "your tipe should be int\n";
                        return;
                    }
                }
            }
            values.push_back(value);
            str1 >> s2;
        }
        std::ofstream os(name + ".txt", std::ios::app);
        for (int i = 0; i < values.size(); i++)
        {
            os << values[i] << "  ,  ";
        }
        os << '\n';
        os.close();
    }
    void Create(std::string& s) {

        std::stringstream stream(s);
        std::string name;
        stream >> name;
        std::string key, value;
        names.close();
        names.open(entity_names, std::ios::app);
        bool t = find(name);
        if (t) {
            std::cout << "the same entity name already exist\n";
            return;
        }
        std::vector<std::string> key1;
        std::vector<std::string> value1;
        t = true;
        bool exept = true;
        std::cout << '\t';
        std::cin >> key;
        while (key != "all") {
            t = false;
            std::cin >> value;
            if (value != "string" && value != "int") {
                exept = false;
                key1.clear();
                value1.clear();
                break;
            }
            key1.push_back(key);
            value1.push_back(value);
            std::cout << '\t';
            std::cin >> key;
        }
        if (t) {
            std::cout << "\nyou can't create entity whith 0 variables\n";
            return;
        }
        std::ofstream of(name + ".txt");
        of.close();
        names << name << '\t';
        for (int i = 0; i < key1.size(); i++)
        {
            names << key1[i] << ' ' << value1[i] << " , ";
        }
        names << '\n';
        names.close();
        names.open(entity_names, std::ios::app);
    }
private:
    bool find(std::string& name) {
        std::ifstream istr(entity_names);
        while (!istr.eof()) {
            std::string s = "", s2 = "";
            bool t = true;
            std::getline(istr, s);
            for (int i = 0; i < s.size(); i++)
            {
                if (s[i] == '\t' || s[i] == '\n' || s[i] == ' ') {
                    if (s2 != name) {
                        break;
                    }
                    istr.close();
                    return true;
                }
                s2 += s[i];
            }
        }
        istr.close();
        return false;
    }
    bool suitsNames(std::string& file_name, std::string& key) {
        std::ifstream fstream(file_name + ".txt");
        while (!fstream.eof()) {
            std::string s1,s2;
            std::getline(fstream, s1);
            std::stringstream stre(s1);
            stre >> s2;
            if (key == s2) {
                fstream.close();
                return true;
            }
        }
        fstream.close();
        return false;
    }
    std::string getTypes(std::string& file_name) {
        std::string text;
        std::fstream fs(entity_names);
        while (!fs.eof())
        {
            std::string a;
            std::getline(fs, a);
            std::stringstream str(a);
            str >> text;
            if (text == file_name) {
                fs.close();
                return a;
            }
        }
        text = "";
        fs.close();
        return text;
    }
    std::string getText(std::string& file_name, std::string& key, std::string& cur) {
        std::ifstream fstream(file_name + ".txt");
        std::string text;
        while (!fstream.eof()) {
            std::string s1, s2;
            std::getline(fstream, s1);
            std::stringstream stre(s1);
            stre >> s2;
            if (key == s2) {
                cur = s1;
            }
            else {
                text += s1+'\n';
            }
        }
        text.erase(text.size() - 1, 1);
        fstream.close();
        return text;
    }
};
int main() {
     ClassEntity c;
     c.Orders();
}
