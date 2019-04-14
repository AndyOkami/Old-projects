                                                                                                                       
                                                                   dddddddd                                            
RRRRRRRRRRRRRRRRR                                                  d::::::d                                            
R::::::::::::::::R                                                 d::::::d                                            
R::::::RRRRRR:::::R                                                d::::::d                                            
RR:::::R     R:::::R                                               d:::::d                                             
  R::::R     R:::::R    eeeeeeeeeeee    aaaaaaaaaaaaa      ddddddddd:::::d    mmmmmmm    mmmmmmm       eeeeeeeeeeee    
  R::::R     R:::::R  ee::::::::::::ee  a::::::::::::a   dd::::::::::::::d  mm:::::::m  m:::::::mm   ee::::::::::::ee  
  R::::RRRRRR:::::R  e::::::eeeee:::::eeaaaaaaaaa:::::a d::::::::::::::::d m::::::::::mm::::::::::m e::::::eeeee:::::ee
  R:::::::::::::RR  e::::::e     e:::::e         a::::ad:::::::ddddd:::::d m::::::::::::::::::::::me::::::e     e:::::e
  R::::RRRRRR:::::R e:::::::eeeee::::::e  aaaaaaa:::::ad::::::d    d:::::d m:::::mmm::::::mmm:::::me:::::::eeeee::::::e
  R::::R     R:::::Re:::::::::::::::::e aa::::::::::::ad:::::d     d:::::d m::::m   m::::m   m::::me:::::::::::::::::e 
  R::::R     R:::::Re::::::eeeeeeeeeee a::::aaaa::::::ad:::::d     d:::::d m::::m   m::::m   m::::me::::::eeeeeeeeeee  
  R::::R     R:::::Re:::::::e         a::::a    a:::::ad:::::d     d:::::d m::::m   m::::m   m::::me:::::::e           
RR:::::R     R:::::Re::::::::e        a::::a    a:::::ad::::::ddddd::::::ddm::::m   m::::m   m::::me::::::::e          
R::::::R     R:::::R e::::::::eeeeeeeea:::::aaaa::::::a d:::::::::::::::::dm::::m   m::::m   m::::m e::::::::eeeeeeee  
R::::::R     R:::::R  ee:::::::::::::e a::::::::::aa:::a d:::::::::ddd::::dm::::m   m::::m   m::::m  ee:::::::::::::e  
RRRRRRRR     RRRRRRR    eeeeeeeeeeeeee  aaaaaaaaaa  aaaa  ddddddddd   dddddmmmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee  

std::unordered_map<BeaconID,BeaconName> IdNameUMap; Valittiin sen takia, että BeaconID ja BeaconName löytyisivät mahdollisimman
nopeasti. Unordered_mapissa tämä on vakioaikaista, minkä takia tämä vaikutti tehokkaimmalta vaihtoehdolta.

std::unordered_map<BeaconName, std::vector<BeaconID>> NameIdUMap; Valittiin sen takia, että samannimiset idt löytyisivät mahdollisimman
nopeasti. Unordered_mapissa tämä on vakioaikaista, minkä takia tämä vaikutti tehokkaimmalta vaihtoehdolta.


std::map<int, BeaconID> BrightnessIdMap; Valittiin sen takia, että kirkkaiman ja himmeimän löytäminen olisi mahdollisimman nopeaa.
Map oli tähän sopiva, koska se on aina järjestyksessä, ja tarvitsemme siitä vain ekan ja vikan arvon (löytäminen mapista vakioaikaista),
koska eka on himmein ja vika on kirkkain majakka.


std::unordered_map<BeaconID, Beacon*> DataUMap; Valittiin sen takia, että Beacon structin sisältöön päästäisiin mahdollisimman
nopeasti käsiksi. Koska järjestyksellä ei ollut merkitystä, ja tiedon löytämisen tietyllä avaimmella piti olla mahdollisimman
nopeaa, unordered_map vaikutti tehokkaimmalta vaihtoehdolta.
