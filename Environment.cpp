class Environment {
public:
    int size_x;
    int size_y;
    std::vector<std::vector<Etat>> map_etat;

    Environment(int size_x, int size_y) {
        this->size_x = size_x;
        this->size_y = size_y;

        for (int y = 0; y < size_y; y++) {
            this->map_etat.push_back({});
            for (int x = 0; x < size_x; x++) {
                this->map_etat[y].push_back(Etat::libre);
            }
        }
    }
};

std::ostream& operator<<(std::ostream& s, Environment& map) {
    for (int y = 0; y < map.size_y; y++) {
        for (int x = 0; x < map.size_x; x++) {
            s << map.map_etat[y][x] << " | ";

        }
        s << std::endl;
    };
    return s;
}