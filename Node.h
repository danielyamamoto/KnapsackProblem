class Node {
    public:
        Node* prev;
        int number, distance;

        Node(int _number);
        int getNumber();
        int getDistance();
        void setDistance(int);
};