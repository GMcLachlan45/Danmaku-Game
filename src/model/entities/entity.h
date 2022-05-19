class Entity{
    int entityId;
    int posX, posY;
    float angle;
    public:
        Entity(int id, int x, int y, float theta);
        Entity(int id, int x, int y);
        ~Entity();
};