#include <bits/stdc++.h>
using namespace std;
template<class T>
class MultiArray{
    int num_of_arrays;
    int* sizes;
    string* names;
    T** elements;
public:
    MultiArray() : num_of_arrays(0) {}
    MultiArray(int num,int* s,string* n){
        num_of_arrays=num;
        names=new string[num];
        sizes=new int[num];
        elements=new T*[num];
        for(int i=0;i<num;i++){
            sizes[i]=s[i];
            names[i]=n[i];
            elements[i]=new T[sizes[i]];
        }
    }
    int get_num_of_arrays(){
        return num_of_arrays;
    }
    int* get_Sizes(){
        return sizes;
    }
    string* get_Names() {
        return names;
    }
    T** get_objects(){
        return elements;
    }
    ~MultiArray(){
        delete[] names;
        delete[] sizes;
        for(int i=0;i<num_of_arrays;i++){
            delete[] elements[i];
        }

    }
    MultiArray(const MultiArray&obj){
        num_of_arrays=obj.num_of_arrays;
        names=new string[num_of_arrays];
        sizes=new int[num_of_arrays];
        elements=new T*[num_of_arrays];
        for(int i=0;i<num_of_arrays;i++){
            sizes[i]=obj.sizes[i];
            names[i]=obj.names[i];
            elements[i]=new T[sizes[i]];
            for (int j = 0; j < sizes[i]; j++) {
                elements[i][j] = obj.elements[i][j];
            }

        }
    }
    void loadFromFile(string arrName, string fileName) {
        ifstream file(fileName);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                istringstream f(line);
                string name;
                f >> name;
                if (name == arrName) {
                    for (int i = 0; i < num_of_arrays; i++) {
                        if (names[i] == arrName) {
                            for (int j = 0; j < sizes[i]; j++) {
                                f >> elements[i][j];
                            }
                        }
                    }
                    break;
                }
            }
            file.close();
        }
    }

    T* subArray(string name, int start_index, int end_index, int step = 1) {
        T* sub_array;
        int subarray_size = 0;

        for (int i = 0; i < num_of_arrays; i++) {
            if (names[i] == name) {
                if (start_index <= end_index) {
                    sub_array = new T[end_index - start_index + 1];
                    for (int j = start_index; j <= end_index; j += step) {
                        sub_array[subarray_size] = elements[i][j];
                        subarray_size++;
                    }
                } else {
                    sub_array = new T[start_index - end_index + 1];
                    for (int j = start_index; j >= end_index; j -= step) {
                        sub_array[subarray_size] = elements[i][j];
                        subarray_size++;
                    }
                }

                return sub_array;
            }
        }

        return nullptr;
    }
    void reverse(string name){
        for (int i = 0; i < num_of_arrays; i++) {
            if (names[i] == name) {
                int start = 0;
                int end = sizes[i] - 1;
                while (start < end) {
                    T value = elements[i][start];
                    elements[i][start] = elements[i][end];
                    elements[i][end] = value;
                    start++;
                    end--;
                }
            }
        }
    }
    void sort(string name){

        for (int i = 0; i < num_of_arrays; i++) {
            if (names[i] == name) {
                int size=sizes[i];
                for (int k = 0; k < size - 1; k++) {
                  for (int j = 0; j < size  -k- 1; j++) {
                        if (elements[i][j] > elements[i][j + 1]) {
                            T value = elements[i][j];
                            elements[i][j] = elements[i][j + 1];
                           elements[i][j + 1] = value;
                        }
                    }
                }
                return;
            }
        }
    }
    bool search(T item) {
        for (int i = 0; i < num_of_arrays; i++) {
            for (int j = 0; j < sizes[i]; j++) {
                if (elements[i][j] == item) {
                    return true;
                }
            }
        }

        return false;
    }
    T& operator()(string name, int index) {

        for (int i = 0; i < num_of_arrays; i++) {
            if (names[i] == name) {
                if (index >= 0) {
                    return elements[i][index];
                } else {

                    return elements[i][sizes[i] + index];
                }
            }
        }
    }

    MultiArray split(const string name) {
        MultiArray<T> obj;
        for (int i = 0; i < num_of_arrays; i++) {
            if (names[i] == name) {
                int size_f = sizes[i] / 2;
                int size_s = sizes[i] - size_f;

                obj.num_of_arrays = 2;
                obj.sizes = new int[2]{size_f, size_s};
                obj.names = new string[2]{"first", "second"};
                obj.elements = new T*[2];
                obj.elements[0] = new T[size_f];
                obj.elements[1] = new T[size_s];

                for (int j = 0; j < size_f; j++) {
                    obj.elements[0][j] = elements[i][j];
                }

                for (int j = 0; j < size_s; j++) {
                    obj.elements[1][j] = elements[i][j + size_f];
                }

                cout << " first split array: ";
                for (int k = 0; k < obj.sizes[0]; k++) {
                    cout << obj.elements[0][k] << " ";
                }
                cout << endl;

                cout << "second split array: ";
                for (int k = 0; k < obj.sizes[1]; k++) {
                    cout << obj.elements[1][k] << " ";
                }

                return obj;
            }
        }

        return obj;
    }
    T* merge() {
        int t_size = 0;
        for (int i = 0; i < num_of_arrays; i++) {
            t_size += sizes[i];
        }

        T* merged = new T[t_size];
        int index = 0;

        for (int i = 0; i < num_of_arrays; i++) {
            for (int j = 0; j < sizes[i]; j++) {
                merged[index++] = elements[i][j];
            }
        }
        cout << "Merged array: ";
        for (int i = 0; i < t_size; i++) {
            cout << merged[i] << " ";
        }
        cout << endl;


        return merged;
    }
    void applyToArray(string name, void (*func)(T&)) {
        for (int i = 0; i < num_of_arrays; i++) {
            if (names[i] == name) {
                for (int j = 0; j < sizes[i]; j++) {
                    func(elements[i][j]);
                }
                return;
            }
        }
    }
    friend ostream& operator<<(ostream& os, const MultiArray& obj) {
        for (int i = 0; i < obj.num_of_arrays; i++) {
            os << obj.names[i] << ": ";
            for (int j = 0; j < obj.sizes[i]; j++) {
                os << (obj.elements[i][j]) << " ";
            }
            os <<endl;
        }
        return os;
    }

};
template <typename T>
void square(T& x) {
    x =x*x;
}

int main() {
    int *size_arr = new int[4];
    size_arr[0] = 5;
    size_arr[1] = 5;
    size_arr[2] = 5;
    size_arr[3] = 5;
    string *names_arr = new string[4];
    names_arr[0] = "age";
    names_arr[1] = "scores";
    names_arr[2] = "year";
    names_arr[3] = "month";

    MultiArray<int> array_file(4, size_arr, names_arr);

    array_file.loadFromFile("age", "grades.txt");
    array_file.loadFromFile("scores", "grades.txt");
    array_file.loadFromFile("year", "grades.txt");
    array_file.loadFromFile("month", "grades.txt");
    for (int i = 0; i < array_file.get_num_of_arrays(); i++) {
        cout << array_file.get_Names()[i] << ": ";
        for (int j = 0; j < array_file.get_Sizes()[i]; j++) { //load function output
            cout << array_file.get_objects()[i][j] << " ";
        }
        cout << endl;
    }
    int * subarray=array_file.subArray("age",1,0,1);
    cout<<"sub array:";
    for(int i=0;i<2;i++){ //subarray function output
    cout<<subarray[i]<<" ";
     }
    cout<<endl;
     array_file.reverse("year");   //reverse function output
     cout<<"reversed array:";
    for (int j = 0; j < array_file.get_Sizes()[2]; j++){
      cout <<array_file.get_objects()[2][j] << " ";}
    cout<<endl;
    array_file.sort("scores");//sort function output
    cout<<"sorted array:";
    for (int j = 0; j < array_file.get_Sizes()[1]; j++){
       cout << array_file.get_objects()[1][j] << " ";}
    cout<<endl;
    cout<<"result of search:";
     if (array_file.search(20)) {//search function output
       cout << "found";
     } else {
        cout << "not found";
    }
     cout<<endl;

    //operator output
    cout<<array_file("age",1)<<endl;
    cout<<array_file("scores",-2)<<endl;
    cout<<"split of array:"<<endl;
    MultiArray<int> splitResult = array_file.split("year");//split array function output
    cout<<endl;
    int * mergedArray = array_file.merge();//merge function output
    cout<<endl;

    array_file.applyToArray("age",square);
    array_file.applyToArray("scores", square);
    array_file.applyToArray("year", square);
    array_file.applyToArray("month", square);

    for (int i = 0; i < array_file.get_num_of_arrays(); i++) {//square function output
        cout << array_file.get_Names()[i] << ": ";
        for (int j = 0; j < array_file.get_Sizes()[i]; j++) {
            cout << array_file.get_objects()[i][j] << " ";
        }
        cout << endl;
    }












}