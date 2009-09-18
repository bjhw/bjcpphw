class Location {
    public:
        Location(int xVal, int yVal);
        int getX();
        int getY();
        void translate(int dx, int dy);

    private:
        int x, y;
};
