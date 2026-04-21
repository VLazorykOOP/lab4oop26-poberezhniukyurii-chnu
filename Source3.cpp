// Компіляція: g++ -std=c++17 -o program all_tasks_simple.cpp

#include <iostream>
#include <string>
#include <cmath>
#include <Windows.h>
using namespace std;


// ================================================================
//  ЗАВДАННЯ 1.4 — VectorShort
//  Масив чисел типу short з перевантаженими операторами
// ================================================================

class VectorShort {
private:
    short* data;    // масив елементів
    int    size;    // кількість елементів
    int    error;   // 0 = ОК, 1 = поганий розмір, 2 = ділення на нуль, 3 = вихід за межі

public:

    // Конструктор без параметрів — створює вектор з одного нуля
    VectorShort() {
        size = 1;
        error = 0;
        data = new short[1];
        data[0] = 0;
    }

    // Конструктор з розміром — всі елементи = 0
    VectorShort(int sz) {
        error = 0;
        if (sz <= 0) {
            sz = 1;
            error = 1;
        }
        size = sz;
        data = new short[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }

    // Конструктор з розміром і початковим значенням
    VectorShort(int sz, short val) {
        error = 0;
        if (sz <= 0) {
            sz = 1;
            error = 1;
        }
        size = sz;
        data = new short[size];
        for (int i = 0; i < size; i++) {
            data[i] = val;
        }
    }

    // Конструктор копіювання
    VectorShort(const VectorShort& other) {
        size = other.size;
        error = other.error;
        data = new short[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    // Деструктор — звільняємо пам'ять
    ~VectorShort() {
        delete[] data;
    }

    int getSize()  const { return size; }
    int getError() const { return error; }

    // --- Унарні оператори ---

    // Префіксний ++ : збільшує кожен елемент на 1
    VectorShort& operator++() {
        for (int i = 0; i < size; i++) data[i]++;
        return *this;
    }

    // Постфіксний ++ : зберігає копію, потім збільшує
    VectorShort operator++(int) {
        VectorShort copy(*this);
        ++(*this);
        return copy;
    }

    // Префіксний --
    VectorShort& operator--() {
        for (int i = 0; i < size; i++) data[i]--;
        return *this;
    }

    // Постфіксний --
    VectorShort operator--(int) {
        VectorShort copy(*this);
        --(*this);
        return copy;
    }

    // Унарний мінус: змінює знак кожного елемента
    VectorShort operator-() const {
        VectorShort result(*this);
        for (int i = 0; i < size; i++) result.data[i] = -data[i];
        return result;
    }

    // Побітове NOT кожного елемента
    VectorShort operator~() const {
        VectorShort result(*this);
        for (int i = 0; i < size; i++) result.data[i] = ~data[i];
        return result;
    }

    // --- Оператор присвоєння ---

    VectorShort& operator=(const VectorShort& other) {
        if (this == &other) return *this; // захист від самоприсвоєння
        delete[] data;
        size = other.size;
        error = other.error;
        data = new short[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
        return *this;
    }

    // --- Оператори += і -= ---

    VectorShort& operator+=(const VectorShort& other) {
        int n = min(size, other.size);
        for (int i = 0; i < n; i++) data[i] += other.data[i];
        return *this;
    }

    VectorShort& operator-=(const VectorShort& other) {
        int n = min(size, other.size);
        for (int i = 0; i < n; i++) data[i] -= other.data[i];
        return *this;
    }

    VectorShort& operator*=(short val) {
        for (int i = 0; i < size; i++) data[i] *= val;
        return *this;
    }

    VectorShort& operator/=(short val) {
        if (val == 0) { error = 2; return *this; }
        for (int i = 0; i < size; i++) data[i] /= val;
        return *this;
    }

    VectorShort& operator%=(short val) {
        if (val == 0) { error = 2; return *this; }
        for (int i = 0; i < size; i++) data[i] %= val;
        return *this;
    }

    // --- Індексування ---

    short& operator[](int idx) {
        if (idx < 0 || idx >= size) {
            error = 3;
            return data[0]; // повертаємо перший елемент при помилці
        }
        return data[idx];
    }

    const short& operator[](int idx) const {
        if (idx < 0 || idx >= size) return data[0];
        return data[idx];
    }

    // () повертає розмір вектора
    int operator()() const { return size; }

    // --- Порівняння ---

    bool operator==(const VectorShort& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const VectorShort& other) const {
        return !(*this == other);
    }

    // --- Оголошення дружніх функцій ---

    friend VectorShort operator+(const VectorShort& a, const VectorShort& b);
    friend VectorShort operator-(const VectorShort& a, const VectorShort& b);
    friend VectorShort operator*(const VectorShort& a, short val);
    friend VectorShort operator/(const VectorShort& a, short val);
    friend VectorShort operator%(const VectorShort& a, short val);
    friend VectorShort operator^(const VectorShort& a, const VectorShort& b);
    friend VectorShort operator&(const VectorShort& a, const VectorShort& b);
    friend VectorShort operator|(const VectorShort& a, const VectorShort& b);
    friend bool operator>(const VectorShort& a, const VectorShort& b);
    friend bool operator<(const VectorShort& a, const VectorShort& b);
    friend ostream& operator<<(ostream& os, const VectorShort& v);
    friend istream& operator>>(istream& is, VectorShort& v);
};

// --- Бінарні арифметичні оператори ---

VectorShort operator+(const VectorShort& a, const VectorShort& b) {
    int n = min(a.size, b.size);
    VectorShort result(n);
    for (int i = 0; i < n; i++) result.data[i] = a.data[i] + b.data[i];
    return result;
}

VectorShort operator-(const VectorShort& a, const VectorShort& b) {
    int n = min(a.size, b.size);
    VectorShort result(n);
    for (int i = 0; i < n; i++) result.data[i] = a.data[i] - b.data[i];
    return result;
}

VectorShort operator*(const VectorShort& a, short val) {
    VectorShort result(a);
    for (int i = 0; i < result.size; i++) result.data[i] *= val;
    return result;
}

VectorShort operator/(const VectorShort& a, short val) {
    VectorShort result(a);
    if (val == 0) { result.error = 2; return result; }
    for (int i = 0; i < result.size; i++) result.data[i] /= val;
    return result;
}

VectorShort operator%(const VectorShort& a, short val) {
    VectorShort result(a);
    if (val == 0) { result.error = 2; return result; }
    for (int i = 0; i < result.size; i++) result.data[i] %= val;
    return result;
}

VectorShort operator^(const VectorShort& a, const VectorShort& b) {
    int n = min(a.size, b.size);
    VectorShort result(n);
    for (int i = 0; i < n; i++) result.data[i] = a.data[i] ^ b.data[i];
    return result;
}

VectorShort operator&(const VectorShort& a, const VectorShort& b) {
    int n = min(a.size, b.size);
    VectorShort result(n);
    for (int i = 0; i < n; i++) result.data[i] = a.data[i] & b.data[i];
    return result;
}

VectorShort operator|(const VectorShort& a, const VectorShort& b) {
    int n = min(a.size, b.size);
    VectorShort result(n);
    for (int i = 0; i < n; i++) result.data[i] = a.data[i] | b.data[i];
    return result;
}

// Порівняння за сумою всіх елементів
long vectorSum(const VectorShort& v) {
    long sum = 0;
    for (int i = 0; i < v.getSize(); i++) sum += v[i];
    return sum;
}

bool operator>(const VectorShort& a, const VectorShort& b) { return vectorSum(a) > vectorSum(b); }
bool operator<(const VectorShort& a, const VectorShort& b) { return vectorSum(a) < vectorSum(b); }

// Вивід у консоль
ostream& operator<<(ostream& os, const VectorShort& v) {
    os << "[";
    for (int i = 0; i < v.size; i++) {
        os << v.data[i];
        if (i < v.size - 1) os << ", ";
    }
    os << "]";
    return os;
}

// Введення з консолі
istream& operator>>(istream& is, VectorShort& v) {
    cout << "Введіть " << v.size << " чисел (short): ";
    for (int i = 0; i < v.size; i++) is >> v.data[i];
    return is;
}


// ================================================================
//  ЗАВДАННЯ 2.3 — DomainIPMap
//  Асоціативний масив: домен <-> IP
// ================================================================

class DomainIPMap {
private:
    string* domains;
    string* ips;
    int     size;
    int     capacity;
    int     error; // 0 = ОК, 1 = не знайдено

    // Збільшуємо масив удвічі, коли місця не вистачає
    void grow() {
        int newCapacity = capacity * 2;
        string* newDomains = new string[newCapacity];
        string* newIps = new string[newCapacity];
        for (int i = 0; i < size; i++) {
            newDomains[i] = domains[i];
            newIps[i] = ips[i];
        }
        delete[] domains;
        delete[] ips;
        domains = newDomains;
        ips = newIps;
        capacity = newCapacity;
    }

public:

    DomainIPMap() {
        capacity = 8;
        size = 0;
        error = 0;
        domains = new string[capacity];
        ips = new string[capacity];
    }

    ~DomainIPMap() {
        delete[] domains;
        delete[] ips;
    }

    int getSize()  const { return size; }
    int getError() const { return error; }

    // Додати або оновити запис
    void add(const string& domain, const string& ip) {
        // Якщо домен вже є — оновлюємо IP
        for (int i = 0; i < size; i++) {
            if (domains[i] == domain) {
                ips[i] = ip;
                return;
            }
        }
        // Інакше додаємо новий запис
        if (size >= capacity) grow();
        domains[size] = domain;
        ips[size] = ip;
        size++;
    }

    // Видалити запис за доменом
    bool remove(const string& domain) {
        for (int i = 0; i < size; i++) {
            if (domains[i] == domain) {
                // Зсуваємо всі наступні записи на одну позицію назад
                for (int j = i; j < size - 1; j++) {
                    domains[j] = domains[j + 1];
                    ips[j] = ips[j + 1];
                }
                size--;
                return true;
            }
        }
        return false;
    }

    // Знайти IP за доменом через []
    string& operator[](const string& domain) {
        for (int i = 0; i < size; i++) {
            if (domains[i] == domain) {
                error = 0;
                return ips[i];
            }
        }
        // Домен не знайдено — створюємо порожній запис
        error = 1;
        if (size >= capacity) grow();
        domains[size] = domain;
        ips[size] = "";
        return ips[size++];
    }

    // Знайти домен за IP через ()
    string operator()(const string& ip) {
        for (int i = 0; i < size; i++) {
            if (ips[i] == ip) {
                error = 0;
                return domains[i];
            }
        }
        error = 1;
        return "(не знайдено)";
    }

    friend ostream& operator<<(ostream& os, const DomainIPMap& m);
    friend istream& operator>>(istream& is, DomainIPMap& m);
};

ostream& operator<<(ostream& os, const DomainIPMap& m) {
    if (m.size == 0) {
        os << "  (таблиця порожня)\n";
        return os;
    }
    os << "+---------------------------+-------------------+\n";
    os << "| Домен                     | IP-адреса         |\n";
    os << "+---------------------------+-------------------+\n";
    for (int i = 0; i < m.size; i++) {
        string d = m.domains[i];
        string ip = m.ips[i];
        // Вирівнюємо рядки по ширині стовпців
        os << "| " << d << string(max(0, 26 - (int)d.size()), ' ')
            << "| " << ip << string(max(0, 18 - (int)ip.size()), ' ') << "|\n";
    }
    os << "+---------------------------+-------------------+\n";
    return os;
}

istream& operator>>(istream& is, DomainIPMap& m) {
    int n;
    cout << "Скільки пар ввести? ";
    is >> n;
    for (int i = 0; i < n; i++) {
        string domain, ip;
        cout << "Домен " << i + 1 << ": "; is >> domain;
        cout << "IP    " << i + 1 << ": "; is >> ip;
        m.add(domain, ip);
    }
    return is;
}


// ================================================================
//  ЗАВДАННЯ 3.4 — Matrix3F
//  Масив тривимірних векторів (x, y, z)
// ================================================================

// Допоміжна структура — один 3D-вектор
struct Vector3F {
    float x, y, z;

    Vector3F(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : x(x), y(y), z(z) {
    }

    Vector3F operator+(const Vector3F& o) const { return Vector3F(x + o.x, y + o.y, z + o.z); }
    Vector3F operator-(const Vector3F& o) const { return Vector3F(x - o.x, y - o.y, z - o.z); }

    bool operator==(const Vector3F& o) const {
        return fabs(x - o.x) < 1e-6f &&
            fabs(y - o.y) < 1e-6f &&
            fabs(z - o.z) < 1e-6f;
    }
    bool operator!=(const Vector3F& o) const { return !(*this == o); }

    // Векторний (хресний) добуток
    Vector3F cross(const Vector3F& o) const {
        return Vector3F(
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        );
    }

    // Довжина вектора
    float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    friend ostream& operator<<(ostream& os, const Vector3F& v) {
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }

    friend istream& operator>>(istream& is, Vector3F& v) {
        cout << "x y z: ";
        return is >> v.x >> v.y >> v.z;
    }
};

class Matrix3F {
private:
    Vector3F* vectors;  // масив 3D-векторів
    int       n;        // кількість векторів
    int       error;    // 0 = ОК, 1 = поганий розмір, 2 = вихід за межі, 3 = ділення на нуль

    static int objectCount; // скільки об'єктів Matrix3F існує зараз

public:

    // Конструктор без параметрів — порожня матриця
    Matrix3F() {
        vectors = nullptr;
        n = 0;
        error = 0;
        objectCount++;
    }

    // Конструктор з розміром — всі вектори = (0, 0, 0)
    Matrix3F(int size) {
        error = 0;
        if (size <= 0) {
            vectors = nullptr;
            n = 0;
            error = 1;
        }
        else {
            n = size;
            vectors = new Vector3F[n]; // Vector3F() за замовчуванням = (0,0,0)
        }
        objectCount++;
    }

    // Конструктор: розмір + однакове значення x,y,z для всіх векторів
    Matrix3F(int size, float val) {
        error = 0;
        if (size <= 0) {
            vectors = nullptr;
            n = 0;
            error = 1;
        }
        else {
            n = size;
            vectors = new Vector3F[n];
            for (int i = 0; i < n; i++) vectors[i] = Vector3F(val, val, val);
        }
        objectCount++;
    }

    // Конструктор: розмір + x, y, z для всіх векторів
    Matrix3F(int size, float x, float y, float z) {
        error = 0;
        if (size <= 0) {
            vectors = nullptr;
            n = 0;
            error = 1;
        }
        else {
            n = size;
            vectors = new Vector3F[n];
            for (int i = 0; i < n; i++) vectors[i] = Vector3F(x, y, z);
        }
        objectCount++;
    }

    // Конструктор копіювання
    Matrix3F(const Matrix3F& other) {
        n = other.n;
        error = other.error;
        if (n > 0) {
            vectors = new Vector3F[n];
            for (int i = 0; i < n; i++) vectors[i] = other.vectors[i];
        }
        else {
            vectors = nullptr;
        }
        objectCount++;
    }

    ~Matrix3F() {
        delete[] vectors;
        objectCount--;
    }

    int getN()     const { return n; }
    int getError() const { return error; }
    static int getObjectCount() { return objectCount; }

    // --- Унарні оператори ---

    Matrix3F& operator++() {
        for (int i = 0; i < n; i++) {
            vectors[i].x++;
            vectors[i].y++;
            vectors[i].z++;
        }
        return *this;
    }

    Matrix3F operator++(int) {
        Matrix3F copy(*this);
        ++(*this);
        return copy;
    }

    Matrix3F& operator--() {
        for (int i = 0; i < n; i++) {
            vectors[i].x--;
            vectors[i].y--;
            vectors[i].z--;
        }
        return *this;
    }

    Matrix3F operator--(int) {
        Matrix3F copy(*this);
        --(*this);
        return copy;
    }

    Matrix3F operator-() const {
        Matrix3F result(n);
        for (int i = 0; i < n; i++) {
            result.vectors[i].x = -vectors[i].x;
            result.vectors[i].y = -vectors[i].y;
            result.vectors[i].z = -vectors[i].z;
        }
        return result;
    }

    // --- Оператор присвоєння ---

    Matrix3F& operator=(const Matrix3F& other) {
        if (this == &other) return *this;
        delete[] vectors;
        n = other.n;
        error = other.error;
        if (n > 0) {
            vectors = new Vector3F[n];
            for (int i = 0; i < n; i++) vectors[i] = other.vectors[i];
        }
        else {
            vectors = nullptr;
        }
        return *this;
    }

    // --- Індексування ---

    Vector3F& operator[](int idx) {
        if (idx < 0 || idx >= n) {
            error = 2;
            return vectors[n > 0 ? n - 1 : 0];
        }
        return vectors[idx];
    }

    const Vector3F& operator[](int idx) const {
        if (idx < 0 || idx >= n) return vectors[n > 0 ? n - 1 : 0];
        return vectors[idx];
    }

    // () повертає кількість векторів
    int operator()() const { return n; }

    // --- Порівняння за сумарною довжиною всіх векторів ---

    float totalLength() const {
        float sum = 0;
        for (int i = 0; i < n; i++) sum += vectors[i].length();
        return sum;
    }

    bool operator==(const Matrix3F& o) const {
        if (n != o.n) return false;
        for (int i = 0; i < n; i++) if (vectors[i] != o.vectors[i]) return false;
        return true;
    }
    bool operator!=(const Matrix3F& o) const { return !(*this == o); }
    bool operator> (const Matrix3F& o) const { return totalLength() > o.totalLength(); }
    bool operator< (const Matrix3F& o) const { return totalLength() < o.totalLength(); }
    bool operator>=(const Matrix3F& o) const { return totalLength() >= o.totalLength(); }
    bool operator<=(const Matrix3F& o) const { return totalLength() <= o.totalLength(); }

    // --- Оголошення дружніх функцій ---

    friend Matrix3F operator+(const Matrix3F& a, const Matrix3F& b);
    friend Matrix3F operator-(const Matrix3F& a, const Matrix3F& b);
    friend Matrix3F operator*(const Matrix3F& a, const Matrix3F& b);
    friend Matrix3F operator*(const Matrix3F& a, float val);
    friend Matrix3F operator/(const Matrix3F& a, const Matrix3F& b);
    friend Matrix3F operator/(const Matrix3F& a, int val);
    friend Matrix3F operator%(const Matrix3F& a, int val);
    friend ostream& operator<<(ostream& os, const Matrix3F& m);
    friend istream& operator>>(istream& is, Matrix3F& m);
};

int Matrix3F::objectCount = 0;

// --- Бінарні оператори Matrix3F ---

Matrix3F operator+(const Matrix3F& a, const Matrix3F& b) {
    int n = min(a.n, b.n);
    Matrix3F result(n);
    for (int i = 0; i < n; i++) result.vectors[i] = a.vectors[i] + b.vectors[i];
    return result;
}

Matrix3F operator-(const Matrix3F& a, const Matrix3F& b) {
    int n = min(a.n, b.n);
    Matrix3F result(n);
    for (int i = 0; i < n; i++) result.vectors[i] = a.vectors[i] - b.vectors[i];
    return result;
}

// Множення покоординатно
Matrix3F operator*(const Matrix3F& a, const Matrix3F& b) {
    int n = min(a.n, b.n);
    Matrix3F result(n);
    for (int i = 0; i < n; i++) {
        result.vectors[i].x = a.vectors[i].x * b.vectors[i].x;
        result.vectors[i].y = a.vectors[i].y * b.vectors[i].y;
        result.vectors[i].z = a.vectors[i].z * b.vectors[i].z;
    }
    return result;
}

Matrix3F operator*(const Matrix3F& a, float val) {
    Matrix3F result(a);
    for (int i = 0; i < result.n; i++) {
        result.vectors[i].x *= val;
        result.vectors[i].y *= val;
        result.vectors[i].z *= val;
    }
    return result;
}

// Ділення = векторний (хресний) добуток відповідних векторів
Matrix3F operator/(const Matrix3F& a, const Matrix3F& b) {
    int n = min(a.n, b.n);
    Matrix3F result(n);
    for (int i = 0; i < n; i++) result.vectors[i] = a.vectors[i].cross(b.vectors[i]);
    return result;
}

Matrix3F operator/(const Matrix3F& a, int val) {
    Matrix3F result(a);
    if (val == 0) { result.error = 3; return result; }
    for (int i = 0; i < result.n; i++) {
        result.vectors[i].x /= val;
        result.vectors[i].y /= val;
        result.vectors[i].z /= val;
    }
    return result;
}

Matrix3F operator%(const Matrix3F& a, int val) {
    Matrix3F result(a);
    if (val == 0) { result.error = 3; return result; }
    for (int i = 0; i < result.n; i++) {
        result.vectors[i].x = fmod(result.vectors[i].x, (float)val);
        result.vectors[i].y = fmod(result.vectors[i].y, (float)val);
        result.vectors[i].z = fmod(result.vectors[i].z, (float)val);
    }
    return result;
}

ostream& operator<<(ostream& os, const Matrix3F& m) {
    os << "Matrix3F [кількість векторів = " << m.n << "]:\n";
    for (int i = 0; i < m.n; i++) {
        os << "  [" << i << "] " << m.vectors[i] << "\n";
    }
    return os;
}

istream& operator>>(istream& is, Matrix3F& m) {
    for (int i = 0; i < m.n; i++) {
        cout << "  Вектор [" << i << "] ";
        is >> m.vectors[i];
    }
    return is;
}


// ================================================================
//  МЕНЮ: VectorShort
// ================================================================

// Зчитати новий вектор з консолі
VectorShort inputVector(const string& name) {
    int sz;
    cout << "Розмір вектора " << name << ": ";
    cin >> sz;
    VectorShort v(sz);
    cin >> v;
    return v;
}

void menuVectorShort() {
    VectorShort v1, v2;
    bool hasV1 = false, hasV2 = false;
    int choice;

    do {
        cout << "\n===== VectorShort =====\n";
        if (hasV1) cout << "v1 = " << v1 << "  (розмір=" << v1.getSize() << ", помилка=" << v1.getError() << ")\n";
        if (hasV2) cout << "v2 = " << v2 << "  (розмір=" << v2.getSize() << ", помилка=" << v2.getError() << ")\n";
        cout << "\n";
        cout << " 1  - Ввести v1\n";
        cout << " 2  - Ввести v2\n";
        cout << " 3  - ++v1 або --v1\n";
        cout << " 4  - Унарний мінус (-v1)\n";
        cout << " 5  - Побітове NOT (~v1)\n";
        cout << " 6  - v1 + v2\n";
        cout << " 7  - v1 - v2\n";
        cout << " 8  - v1 * скаляр\n";
        cout << " 9  - v1 / скаляр\n";
        cout << " 10 - v1 % скаляр\n";
        cout << " 11 - v1 ^ v2  (XOR)\n";
        cout << " 12 - v1 & v2  (AND)\n";
        cout << " 13 - v1 | v2  (OR)\n";
        cout << " 14 - Порівняти v1 і v2\n";
        cout << " 15 - Прочитати v1[індекс]\n";
        cout << " 16 - Змінити v1[індекс]\n";
        cout << " 17 - v2 = v1 (копіювання)\n";
        cout << " 0  - Назад\n";
        cout << "Вибір: ";
        cin >> choice;

        if (choice == 1) {
            v1 = inputVector("v1");
            hasV1 = true;
        }
        else if (choice == 2) {
            v2 = inputVector("v2");
            hasV2 = true;
        }
        else if (choice == 3) {
            if (!hasV1) { cout << "Спочатку введіть v1!\n"; continue; }
            int sub;
            cout << "1 = ++v1 (префікс)  2 = v1++ (постфікс)  3 = --v1: ";
            cin >> sub;
            if (sub == 1) {
                ++v1;
                cout << "++v1 = " << v1 << "\n";
            }
            else if (sub == 2) {
                VectorShort old = v1++;
                cout << "v1++ повертає: " << old << "\n";
                cout << "v1 тепер: " << v1 << "\n";
            }
            else {
                --v1;
                cout << "--v1 = " << v1 << "\n";
            }
        }
        else if (choice == 4) {
            if (!hasV1) { cout << "Спочатку введіть v1!\n"; continue; }
            cout << "-v1 = " << (-v1) << "\n";
        }
        else if (choice == 5) {
            if (!hasV1) { cout << "Спочатку введіть v1!\n"; continue; }
            cout << "~v1 = " << (~v1) << "\n";
        }
        else if (choice == 6) {
            if (!hasV1 || !hasV2) { cout << "Потрібні обидва вектори!\n"; continue; }
            cout << "v1 + v2 = " << (v1 + v2) << "\n";
        }
        else if (choice == 7) {
            if (!hasV1 || !hasV2) { cout << "Потрібні обидва вектори!\n"; continue; }
            cout << "v1 - v2 = " << (v1 - v2) << "\n";
        }
        else if (choice == 8) {
            if (!hasV1) { cout << "Спочатку введіть v1!\n"; continue; }
            short sc;
            cout << "Скаляр: "; cin >> sc;
            cout << "v1 * " << sc << " = " << (v1 * sc) << "\n";
        }
        else if (choice == 9) {
            if (!hasV1) { cout << "Спочатку введіть v1!\n"; continue; }
            short sc;
            cout << "Скаляр: "; cin >> sc;
            VectorShort r = v1 / sc;
            if (r.getError() == 2) cout << "ПОМИЛКА: ділення на нуль!\n";
            else cout << "v1 / " << sc << " = " << r << "\n";
        }
        else if (choice == 10) {
            if (!hasV1) { cout << "Спочатку введіть v1!\n"; continue; }
            short sc;
            cout << "Скаляр: "; cin >> sc;
            VectorShort r = v1 % sc;
            if (r.getError() == 2) cout << "ПОМИЛКА: ділення на нуль!\n";
            else cout << "v1 % " << sc << " = " << r << "\n";
        }
        else if (choice == 11) {
            if (!hasV1 || !hasV2) { cout << "Потрібні обидва вектори!\n"; continue; }
            cout << "v1 ^ v2 = " << (v1 ^ v2) << "\n";
        }
        else if (choice == 12) {
            if (!hasV1 || !hasV2) { cout << "Потрібні обидва вектори!\n"; continue; }
            cout << "v1 & v2 = " << (v1 & v2) << "\n";
        }
        else if (choice == 13) {
            if (!hasV1 || !hasV2) { cout << "Потрібні обидва вектори!\n"; continue; }
            cout << "v1 | v2 = " << (v1 | v2) << "\n";
        }
        else if (choice == 14) {
            if (!hasV1 || !hasV2) { cout << "Потрібні обидва вектори!\n"; continue; }
            cout << boolalpha;
            cout << "v1 >  v2: " << (v1 > v2) << "\n";
            cout << "v1 <  v2: " << (v1 < v2) << "\n";
            cout << "v1 == v2: " << (v1 == v2) << "\n";
            cout << "v1 != v2: " << (v1 != v2) << "\n";
        }
        else if (choice == 15) {
            if (!hasV1) { cout << "Спочатку введіть v1!\n"; continue; }
            int idx;
            cout << "Індекс: "; cin >> idx;
            cout << "v1[" << idx << "] = " << v1[idx];
            if (v1.getError() == 3) cout << "  <-- ПОМИЛКА: вихід за межі!";
            cout << "\n";
        }
        else if (choice == 16) {
            if (!hasV1) { cout << "Спочатку введіть v1!\n"; continue; }
            int idx; short val;
            cout << "Індекс: "; cin >> idx;
            cout << "Нове значення: "; cin >> val;
            v1[idx] = val;
            if (v1.getError() == 3) cout << "ПОМИЛКА: вихід за межі!\n";
            else cout << "v1 тепер = " << v1 << "\n";
        }
        else if (choice == 17) {
            if (!hasV1) { cout << "Спочатку введіть v1!\n"; continue; }
            v2 = v1;
            hasV2 = true;
            cout << "v2 = v1 = " << v2 << "\n";
        }
        else if (choice != 0) {
            cout << "Невірний вибір.\n";
        }

    } while (choice != 0);
}


// ================================================================
//  МЕНЮ: DomainIPMap
// ================================================================

void menuDomainIPMap() {
    DomainIPMap table;
    int choice;

    do {
        cout << "\n===== DomainIPMap =====\n";
        cout << table;
        cout << "\n";
        cout << " 1 - Додати або оновити запис\n";
        cout << " 2 - Видалити запис\n";
        cout << " 3 - Знайти IP за доменом\n";
        cout << " 4 - Знайти домен за IP\n";
        cout << " 5 - Ввести кілька пар одразу\n";
        cout << " 0 - Назад\n";
        cout << "Вибір: ";
        cin >> choice;

        if (choice == 1) {
            string domain, ip;
            cout << "Домен: "; cin >> domain;
            cout << "IP:    "; cin >> ip;
            table.add(domain, ip);
            cout << "Додано.\n";
        }
        else if (choice == 2) {
            string domain;
            cout << "Домен для видалення: "; cin >> domain;
            if (table.remove(domain)) cout << "Видалено.\n";
            else cout << "Домен не знайдено.\n";
        }
        else if (choice == 3) {
            string domain;
            cout << "Домен: "; cin >> domain;
            string ip = table[domain];
            if (table.getError() == 1) cout << "Домен не знайдено.\n";
            else cout << "IP = " << ip << "\n";
        }
        else if (choice == 4) {
            string ip;
            cout << "IP: "; cin >> ip;
            string domain = table(ip);
            if (table.getError() == 1) cout << "IP не знайдено.\n";
            else cout << "Домен = " << domain << "\n";
        }
        else if (choice == 5) {
            cin >> table;
        }
        else if (choice != 0) {
            cout << "Невірний вибір.\n";
        }

    } while (choice != 0);
}


// ================================================================
//  МЕНЮ: Matrix3F
// ================================================================

Matrix3F inputMatrix(const string& name) {
    int sz;
    cout << "Кількість векторів у " << name << ": ";
    cin >> sz;
    Matrix3F m(sz);
    cout << "Введіть " << sz << " вектори:\n";
    cin >> m;
    return m;
}

void menuMatrix3F() {
    Matrix3F m1, m2;
    bool hasM1 = false, hasM2 = false;
    int choice;

    do {
        cout << "\n===== Matrix3F =====\n";
        cout << "Об'єктів Matrix3F зараз: " << Matrix3F::getObjectCount() << "\n";
        if (hasM1) cout << "m1:\n" << m1;
        if (hasM2) cout << "m2:\n" << m2;
        cout << "\n";
        cout << " 1  - Ввести m1\n";
        cout << " 2  - Ввести m2\n";
        cout << " 3  - ++m1 або --m1\n";
        cout << " 4  - Унарний мінус (-m1)\n";
        cout << " 5  - m1 + m2\n";
        cout << " 6  - m1 - m2\n";
        cout << " 7  - m1 * m2  (покоординатно)\n";
        cout << " 8  - m1 * скаляр\n";
        cout << " 9  - m1 / m2  (векторний добуток)\n";
        cout << " 10 - m1 / ціле число\n";
        cout << " 11 - m1 % ціле число\n";
        cout << " 12 - Порівняти m1 і m2\n";
        cout << " 13 - Прочитати m1[індекс]\n";
        cout << " 14 - Змінити m1[індекс]\n";
        cout << " 15 - m2 = m1 (копіювання)\n";
        cout << " 0  - Назад\n";
        cout << "Вибір: ";
        cin >> choice;

        if (choice == 1) {
            m1 = inputMatrix("m1");
            hasM1 = true;
        }
        else if (choice == 2) {
            m2 = inputMatrix("m2");
            hasM2 = true;
        }
        else if (choice == 3) {
            if (!hasM1) { cout << "Спочатку введіть m1!\n"; continue; }
            int sub;
            cout << "1 = ++m1 (префікс)  2 = m1++ (постфікс)  3 = --m1: ";
            cin >> sub;
            if (sub == 1) {
                ++m1;
                cout << "++m1:\n" << m1;
            }
            else if (sub == 2) {
                Matrix3F old = m1++;
                cout << "m1++ повертає:\n" << old;
                cout << "m1 тепер:\n" << m1;
            }
            else {
                --m1;
                cout << "--m1:\n" << m1;
            }
        }
        else if (choice == 4) {
            if (!hasM1) { cout << "Спочатку введіть m1!\n"; continue; }
            cout << "-m1:\n" << (-m1);
        }
        else if (choice == 5) {
            if (!hasM1 || !hasM2) { cout << "Потрібні обидві матриці!\n"; continue; }
            cout << "m1 + m2:\n" << (m1 + m2);
        }
        else if (choice == 6) {
            if (!hasM1 || !hasM2) { cout << "Потрібні обидві матриці!\n"; continue; }
            cout << "m1 - m2:\n" << (m1 - m2);
        }
        else if (choice == 7) {
            if (!hasM1 || !hasM2) { cout << "Потрібні обидві матриці!\n"; continue; }
            cout << "m1 * m2:\n" << (m1 * m2);
        }
        else if (choice == 8) {
            if (!hasM1) { cout << "Спочатку введіть m1!\n"; continue; }
            float sc;
            cout << "Скаляр: "; cin >> sc;
            cout << "m1 * " << sc << ":\n" << (m1 * sc);
        }
        else if (choice == 9) {
            if (!hasM1 || !hasM2) { cout << "Потрібні обидві матриці!\n"; continue; }
            cout << "m1 / m2 (cross product):\n" << (m1 / m2);
        }
        else if (choice == 10) {
            if (!hasM1) { cout << "Спочатку введіть m1!\n"; continue; }
            int val;
            cout << "Дільник: "; cin >> val;
            Matrix3F r = m1 / val;
            if (r.getError() == 3) cout << "ПОМИЛКА: ділення на нуль!\n";
            else cout << "m1 / " << val << ":\n" << r;
        }
        else if (choice == 11) {
            if (!hasM1) { cout << "Спочатку введіть m1!\n"; continue; }
            int val;
            cout << "Дільник: "; cin >> val;
            Matrix3F r = m1 % val;
            if (r.getError() == 3) cout << "ПОМИЛКА: ділення на нуль!\n";
            else cout << "m1 % " << val << ":\n" << r;
        }
        else if (choice == 12) {
            if (!hasM1 || !hasM2) { cout << "Потрібні обидві матриці!\n"; continue; }
            cout << boolalpha;
            cout << "m1 >  m2: " << (m1 > m2) << "\n";
            cout << "m1 <  m2: " << (m1 < m2) << "\n";
            cout << "m1 >= m2: " << (m1 >= m2) << "\n";
            cout << "m1 <= m2: " << (m1 <= m2) << "\n";
            cout << "m1 == m2: " << (m1 == m2) << "\n";
            cout << "m1 != m2: " << (m1 != m2) << "\n";
        }
        else if (choice == 13) {
            if (!hasM1) { cout << "Спочатку введіть m1!\n"; continue; }
            int idx;
            cout << "Індекс: "; cin >> idx;
            cout << "m1[" << idx << "] = " << m1[idx];
            if (m1.getError() == 2) cout << "  <-- ПОМИЛКА: вихід за межі!";
            cout << "\n";
        }
        else if (choice == 14) {
            if (!hasM1) { cout << "Спочатку введіть m1!\n"; continue; }
            int idx;
            cout << "Індекс: "; cin >> idx;
            float x, y, z;
            cout << "Новий вектор x y z: "; cin >> x >> y >> z;
            m1[idx] = Vector3F(x, y, z);
            if (m1.getError() == 2) cout << "ПОМИЛКА: вихід за межі!\n";
            else cout << "m1 тепер:\n" << m1;
        }
        else if (choice == 15) {
            if (!hasM1) { cout << "Спочатку введіть m1!\n"; continue; }
            m2 = m1;
            hasM2 = true;
            cout << "m2 = m1:\n" << m2;
        }
        else if (choice != 0) {
            cout << "Невірний вибір.\n";
        }

    } while (choice != 0);
}


// ================================================================
//  ГОЛОВНЕ МЕНЮ
// ================================================================

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice;

    do {
        cout << "\n==========================================\n";
        cout << "         ОБЕРІТЬ ЗАВДАННЯ\n";
        cout << "==========================================\n";
        cout << " 1 - Завдання 1.4 (VectorShort)\n";
        cout << " 2 - Завдання 2.3 (DomainIPMap)\n";
        cout << " 3 - Завдання 3.4 (Matrix3F)\n";
        cout << " 0 - Вихід\n";
        cout << "==========================================\n";
        cout << "Вибір: ";
        cin >> choice;

        if (choice == 1) menuVectorShort();
        else if (choice == 2) menuDomainIPMap();
        else if (choice == 3) menuMatrix3F();
        else if (choice == 0) cout << "\nДо побачення!\n";
        else cout << "Невірний вибір.\n";

    } while (choice != 0);

    return 0;
}