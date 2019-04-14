// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this with your implementation
}

Datastructures::~Datastructures()
{
    // Replace this with your implementation
}

int Datastructures::beacon_count()
{
    // Return int falue, size is unsigned int so we
    //change it to int with static_cast
    return static_cast<int>(IdNameUMap.size());
}

void Datastructures::clear_beacons()
{
    // Clear all data
    IdNameUMap.clear();
    NameIdUMap.clear();
    DataUMap.clear();
    BrightnessIdMap.clear();

}

std::vector<BeaconID> Datastructures::all_beacons()
{
    std::vector<BeaconID> v;
    // Change int to unsigned long
    unsigned long size = static_cast<unsigned long>(beacon_count());
    v.reserve(size);    // Reserve just enough memory for the vector
    // Go trough the entire map and pushback the keys to vector
    for ( auto it = DataUMap.begin() ; it != DataUMap.end() ; it++)
    {
        v.push_back(it->first);
    }

    return v;
}

std::vector<Beacon*> Datastructures::all_beacons_struct()
{
    std::vector<Beacon*> v;
    unsigned long size = static_cast<unsigned long>(beacon_count());
    v.reserve(size);
    for ( auto it = DataUMap.begin() ; it != DataUMap.end() ; it++)
    {
        v.push_back(it->second);
    }
    return v;
}

bool Datastructures::add_beacon(BeaconID id, const std::string& name, Coord xy, Color color)
{
    //If count is 0, there is no beacons with the same id
    if (IdNameUMap.count(id) == 0)
    {
        // Inserts the data to the containers
        IdNameUMap[id] = name;
        NameIdUMap[name].push_back(id);
        // Calculating the brightness of the beacon
        int brightness = 3 * color.r + 6 * color.g + color.b;
        BrightnessIdMap[brightness]=id;
        DataUMap[id] = new Beacon{id, name, xy, color, brightness};
        return true;
    }
    else {
        return false;
    }
}

std::string Datastructures::get_name(BeaconID id)
{
    // Check that the unordered_map has the id
    if (IdNameUMap.find(id) != IdNameUMap.end())
    {
        return IdNameUMap[id];
    }
    else {
        return NO_NAME;
    }
}

Coord Datastructures::get_coordinates(BeaconID id)
{

    // Check that the unordered_map isn't empty, so the name exists
    if (DataUMap.find(id) != DataUMap.end())
    {
        return DataUMap[id]->coord; // return the coordinates
    }
    else
    {
        return NO_COORD;
    }

}

Color Datastructures::get_color(BeaconID id)
{

    // Check that the unordered_map isn't empty, so the name exists
    if (DataUMap.find(id) != DataUMap.end())
    {
       return DataUMap[id]->color; // return the color
    }
    else
    {
        return NO_COLOR;
    }

}


std::vector<BeaconID> Datastructures::beacons_alphabetically()
{
    std::vector<Beacon*> v = all_beacons_struct();  // Get all ids
    // Sort from beginning to end, the lambda looks for the alphapedical order
    //of the names and is the rule for the sort
    std::sort(v.begin(), v.end(), [] (const Beacon* a, const Beacon* b)
    {return a->name < b->name; });
    std::vector<BeaconID> Idv;
    Idv.reserve(v.size());   //reserve just enough memory
    // Add the sorted ids to the vector
    for (Beacon* it:v)
    {
        Idv.push_back(it->id);
    }
    return Idv;

}

std::vector<BeaconID> Datastructures::beacons_brightness_increasing()
{
    std::vector<Beacon*> v = all_beacons_struct();  // Get all of the beacon structs
    // Sort with the help of the struct
    std::sort(v.begin(), v.end(), [] (const Beacon* a, const Beacon* b)
    {return a->brightness < b->brightness;});
    std::vector<BeaconID> Idv;
    Idv.reserve(v.size());  //reserve just enough memory
    // Add the sorted ids to the vector
    for (Beacon* it:v)
    {
        Idv.push_back(it->id);
    }
    return Idv;
}

BeaconID Datastructures::min_brightness()
{
    // If there are beacons, search the least bright form the map
    // which is the the first value in the map
    if (beacon_count()!=0)
    {
        return BrightnessIdMap.begin()->second;
    }
    else
    {
    // If there is no beacons, return NO_ID
     return NO_ID;
    }
}

BeaconID Datastructures::max_brightness()
{
    // If there are beacons, search the brightest from the map,
    // which is at the end of the map
    if (beacon_count()!=0)
    {
        return BrightnessIdMap.rbegin()->second;
    }
    else
    {
    // If there is no beacons, return NO_ID
     return NO_ID;
    }
}

std::vector<BeaconID> Datastructures::find_beacons(std::string const& name)
{   
    std::vector<BeaconID> v = NameIdUMap[name];
    std::sort(v.begin(), v.end(), [] (const BeaconID a, const BeaconID b ) {return a < b;});
    return v;
}

bool Datastructures::change_beacon_name(BeaconID id, const std::string& newname)
{
    // Check that the unordered_map has the id, so we can do the changes
    // If the beacon is found, change all namedata and return true
    if (DataUMap.find(id) != DataUMap.end())
    {
    BeaconName name = IdNameUMap[id];
    std::swap(IdNameUMap[id], IdNameUMap[id]=newname);
    NameIdUMap.erase(name);
    NameIdUMap[newname];
    std::swap(DataUMap[id]->name, DataUMap[id]->name=newname);
    return true;
    }
    // If the id was not found return false
    return false;
}

bool Datastructures::change_beacon_color(BeaconID id, Color newcolor)
{
    // Check that the unordered_map has the id, so we can do the changes
    // If the beacon is found, change all colordata and return true
    if (DataUMap.find(id) != DataUMap.end())
    {
    int newbrightness = 3 * newcolor.r + 6 * newcolor.g + newcolor.b;
    int oldbrightness = DataUMap[id]->brightness;
    BrightnessIdMap.erase(oldbrightness);
    BrightnessIdMap[newbrightness]=id;
    std::swap(DataUMap[id]->color, DataUMap[id]->color=newcolor);
    std::swap(DataUMap[id]->brightness, DataUMap[id]->brightness=newbrightness);
    return true;

    }
    // If the id was not found, return false
    return false;
}

bool Datastructures::add_lightbeam(BeaconID sourceid, BeaconID targetid)
{
    // Check that the DataUMap has the ids
    // If the beacons are found, change lightdata and return true
    if (DataUMap.find(sourceid) != DataUMap.end() and DataUMap.find(targetid) != DataUMap.end())
    {
        DataUMap[sourceid]->targetid = targetid;
        DataUMap[targetid]->lightsenderids.push_back(sourceid);
        return true;
    }
    // If the id was not found, return false
    return false;
}

std::vector<BeaconID> Datastructures::get_lightsources(BeaconID id)
{
    // Check whether the lightsenderids is empty
    // If so, return an empty vector
    if (DataUMap[id]->lightsenderids.empty())
    {
        std::vector<BeaconID> emptyv;
        return emptyv;
    }
    // Check that the DataUMap has the id
    // If so return the lightsenderids vector
    else if (DataUMap.find(id) != DataUMap.end())
    {
        std::vector v = DataUMap[id]->lightsenderids;
        // Sort the ids
        std::sort(v.begin(), v.end(), [] (const BeaconID a, const BeaconID b ) {return a < b;});
        return v;
    }
    return {{NO_ID}};
}

std::vector<BeaconID> Datastructures::path_outbeam(BeaconID id)
{
    std::vector<BeaconID> path = {};
    // If id found, do the following
    if (DataUMap.count(id) != 0)
    {
        path.push_back(id);
        BeaconID target = DataUMap[id]->targetid;
        // While we still have a target, push it to the vector
        while (!target.empty())
        {
            path.push_back(target);
            target = DataUMap[target]->targetid;
        }
        return path;    // return the vector
    }

    return {{NO_ID}};   // return vector with NO_ID, if id not found
}

bool Datastructures::remove_beacon(BeaconID /*id*/)
{
    // Replace this with your implementation
    return false;
}

std::vector<BeaconID> Datastructures::path_inbeam_longest(BeaconID /*id*/)
{
    // Replace this with your implementation
    return {{NO_ID}};
}

Color Datastructures::total_color(BeaconID /*id*/)
{
    // Replace this with your implementation
    return NO_COLOR;
}
