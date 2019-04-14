// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>
#include <limits>
#include <algorithm>


// Type for beacon IDs
using BeaconID = std::string;

// Type for beacon names
using BeaconName = std::string;


// Return value for cases where required beacon was not found
BeaconID const NO_ID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
std::string const NO_NAME = "-- unknown --";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for color (RGB)
struct Color
{
    int r = NO_VALUE;
    int g = NO_VALUE;
    int b = NO_VALUE;
};

// Equality and non-equality comparisons for Colors
inline bool operator==(Color c1, Color c2) { return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b; }
inline bool operator!=(Color c1, Color c2) { return !(c1==c2); }

// Return value for cases where color was not found
Color const NO_COLOR = {NO_VALUE, NO_VALUE, NO_VALUE};

// Type for light transmission cost (used only in the second assignment)
using Cost = int;

// Return value for cases where cost is unknown
Cost const NO_COST = NO_VALUE;

struct Beacon
{
    BeaconID id;
    BeaconName name;
    Coord coord;
    Color color;
    int brightness;
    BeaconID targetid;
    std::vector<BeaconID> lightsenderids;

};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief Beacon_count gets the amount of beacons
     * @return int size for the unordered map
     */
    int beacon_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief clear_beacons Removes all data from the database
     */
    void clear_beacons();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Goes trough every key in map once.
    /**
     * @brief all_beacons Gets all of the BeaconId:s in a vector
     * @return vector of BeaconId:s
     */
    std::vector<BeaconID> all_beacons();

    // Estimate of performance: n(1)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief add_beacon Adds the beacon to the datacontainer
     * @param id the id of the beacon
     * @param name of the beacon
     * @param xy the coordinates
     * @param color the color
     * @return True if added succesfully, othervise false
     */


    bool add_beacon(BeaconID id, std::string const& name, Coord xy, Color color);

    // Estimate of performance: n(1)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief get_name Gets the name by using the id
     * @param id The Id of the beacon
     * @return BeaconName
     */
    std::string get_name(BeaconID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief get_coordinates Gets the coordinates by using the id
     * @param id The Id of the beacon
     * @return Coord
     */
    Coord get_coordinates(BeaconID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief get_color Gets the color of the beacon by using the id
     * @param id The Id to the beacon
     * @return Color
     */
    Color get_color(BeaconID id);


    // Estimate of performance:O(n)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief beacons_alphabetically Sorts the ids by the alphapedical order of the names
     * @return The sorted vector of ids
     */
    std::vector<BeaconID> beacons_alphabetically();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief beacons_brightness_increasing Sorts the ids by the accending brightness order
     * @return The sorted vector of ids
     */
    std::vector<BeaconID> beacons_brightness_increasing();

    // Estimate of performance:theeta(1)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief min_brightness Tells you the least bright beacon
     * @return Id to the least bright beacon, else NO_ID
     */
    BeaconID min_brightness();

    // Estimate of performance: theeta(1)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief max_brightness Tells you the most bright beacon
     * @return Id to the most bright beacon, else NO_ID
     */
    BeaconID max_brightness();

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: Because of documentation
    /**
     * @brief find_beacons Finds the beacons with a certain name
     * @param name The name we are searching for
     * @return The vector of ids with our searched name
     */
    std::vector<BeaconID> find_beacons(std::string const& name);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief change_beacon_name Changes the name of the beacon in given id
     * @param id The beacon we should rename
     * @param newname The new name of the beacon
     * @return True if change was successfull, else false
     */
    bool change_beacon_name(BeaconID id, std::string const& newname);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief change_beacon_color Changes the color of the beacon in given id
     * @param id The beacon which color we need to change
     * @param newcolor The new color for the beacon
     * @return True if change was successfull, else false
     */
    bool change_beacon_color(BeaconID id, Color newcolor);


    // Estimate of performance: O(1)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief add_lightbeam Add a lightbeam from sourceid to targetid
     * @param sourceid Beacon that emits the light
     * @param targetid Beacon that receives the light
     * @return True if change was succesfull, else false
     */
    bool add_lightbeam(BeaconID sourceid, BeaconID targetid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief get_lightsources Get to vector of ids lightsources
     * @param id Id which lightsources the function is looking for
     * @return Vector of the lightsources
     */
    std::vector<BeaconID> get_lightsources(BeaconID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief path_outbeam Get vector of beacons where the light passes trough
     * @param id The starter beacon
     * @return Vector of beacons (the path of the light) if id found, else {{NO_ID}}
     */
    std::vector<BeaconID> path_outbeam(BeaconID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_beacon(BeaconID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<BeaconID> path_inbeam_longest(BeaconID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Color total_color(BeaconID id);

private:

    // From id to map data
    std::unordered_map<BeaconID,BeaconName> IdNameUMap;

    // From name to id data
    std::unordered_map<BeaconName, std::vector<BeaconID>> NameIdUMap;

    // From id to brightness
    std::map<int, BeaconID> BrightnessIdMap;

    // When we have the idNameUMap data, use it to get more data
    std::unordered_map<BeaconID, Beacon*> DataUMap;

    //std::unordered_map<BeaconID, std::vector<BeaconID>> IdPathUmap;
    // // Estimate of performance: O(n)
    // Short rationale for estimate: Because of documentation
    /**
     * @brief all_beacons_struct Gives a vecor of Beacon*
     * @return Beacon*
     */
    std::vector<Beacon*> all_beacons_struct();

};

#endif // DATASTRUCTURES_HH
