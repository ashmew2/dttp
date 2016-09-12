#include <string>
#include <iostream>
#include <vector>
using namespace std;

class HostSeedMap {
  vector<string> seed_list;
  string host_name;
  string seed_secret;
  string host_secret;
  
public:
  HostSeedMap(string new_host, int capacity = 5) {
    host_name = new_host;
    seed_list.reserve(capacity);
  }

  void register_seed(string new_seed) {
    seed_list.push_back(new_seed);
  }
  
  void unregister_seed(string dying_seed) {
    for(unsigned int i = 0; i < seed_list.size(); i++)
      if(seed_list[i] == dying_seed) {
	seed_list.erase(seed_list.begin() + i);
	break;
      }
  }

  string get_host_name(void) {
    return host_name;
  };

  int number_of_seeds(void) {
    return seed_list.size();
  }

  vector<string> list_of_seeds(void) {
    return seed_list;
  }
};

// TODO: Map Hostname with a hash or set for O(1) lookups with seeds
class Tracker {
  vector<HostSeedMap> host_list;
  // TODO: Do we need the tracker to know itself? Like a tracker ID? 

  Tracker() {
    host_list.reserve(5);
  }
  // has_host should return an Host ID (Vector index of host so we avoid lookups again).
  // TODO: Optimise and use hashing or bin search instead of linear loop
  // So that all other functions simply acccept host id instead of hostname and be more efficient
  
  bool has_host(string ghost) {
    for(unsigned int i = 0; i < host_list.size(); i++)
      if(host_list[i].get_host_name() == ghost)
	return true;

    return false;
  }

  bool host_has_seeds(string ghost) {
    for(unsigned int i = 0; i < host_list.size(); i++)
      if(host_list[i].get_host_name() == ghost)
	if(host_list[i].number_of_seeds() > 0)
	  return true;

    return false;
  }

  vector<string> seeds_of_host(string ghost) {
    // TODO Assume the host exists (Has been checked with tracker.has_host() 
    for(unsigned int i = 0; i < host_list.size(); i++)
      if(host_list[i].get_host_name() == ghost)
	return host_list[i].list_of_seeds();
  }

  // TODO: We should return the host ID so that caller can keep it
  void register_new_host(string new_hostname, vector<string> new_seeds) {
    HostSeedMap *new_host_seed_map = new HostSeedMap(new_hostname, new_seeds.size());
    // TODO: Replace this method with a bulk method as well? 
    for(unsigned int i = 0; i<new_seeds.size(); i++) {
      new_host_seed_map->register_seed(new_seeds[i]);
    }

    host_list.push_back(*new_host_seed_map);
  }

  void unregister_host(string dead_host) {
    for(unsigned int i = 0; i < host_list.size(); i++)
      if(host_list[i].get_host_name() == dead_host) {
	host_list.erase(host_list.begin() + i);
	break;
      }
  }

  bool verify_seed_secret(string hostname, string secret) {
    // TODO: Fix this stub. This always returns true!
    return true;
  }
};
