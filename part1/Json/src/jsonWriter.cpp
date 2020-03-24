#include "Json/jsonWriter.hpp"
#include <string>

void outputBestIndividual(Individual* bestIndividual)
{
    Json::Value best;
    // population["puzzle"] = obj["0"]["puzzle"];
    best["length"] = bestIndividual->frameLength;
    best["width"] = bestIndividual->frameWidth;
    best["pieces"] = bestIndividual->size;

    best["puzzle"] = Json::Value(Json::arrayValue);
    Json::Value &puzzle = best["puzzle"];

    for (int i = 0; i < bestIndividual->size; i++)
    {
        puzzle[i] = Json::Value(Json::arrayValue);

        puzzle[i][0] = bestIndividual->tiles[i].x;
        puzzle[i][1] = bestIndividual->tiles[i].y;
        puzzle[i][2] = bestIndividual->tiles[i].l;
        puzzle[i][3] = bestIndividual->tiles[i].w;
    }

    std::ofstream file_id;
    file_id.open("bestIndividual.json");
    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(best);
    file_id.close();
}