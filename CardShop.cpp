#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
CardShop::CardShop(std::string input_file_name) 
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

template<typename Comparator>
int CardShop::BubbleSort(Comparator comp, std::string key){
  int total_swap = 0;
    for(int i = 0; i < item_count_ - 1; i++)
      for(int j = 0; j < item_count_ - i - 1; j++){
        int a,b = key;
        if(a == "atk"){
          getItem(j)->getAtk()
        }
        else{
          getItem(j)->getDef();
        } 

        if(b == "atk"){
          getItem(j+1)->getAtk()
        }
        else{
          getItem(j+1)->getDef();
        } 
        if(comp(a, b)){
          swap(j, j+1);
          total_swap++;
        }
      }
    return total_swap;
}

template<typename Comparator>
int CardShop::InsertionSort(Comparator comp, std::string key){
  int total_swap = 0;

  for(int i = 1; i < item_count_; i++){
    int a = key == "atk" ? getItem(i-1)->getAtk() : getItem(i-1)->getDef();
    int b = key == "atk" ? getItem(i)->getAtk() : getItem(i)->getDef();

    if(comp(a, b)){
      swap(i-1, i);
      total_swap++;
      for(int j = i - 1; j > 0; j--){
        int a = key == "atk" ? getItem(j-1)->getAtk() : getItem(j-1)->getDef();
        int b = key == "atk" ? getItem(j)->getAtk() : getItem(j)->getDef();
        if(comp(a, b)){
          swap(j-1, j);
          total_swap++;
        } else {
          break;
        }
      }
    }
  }
  return total_swap;
}

template<typename Comparator>
int CardShop::QuickSort(Comparator comp, std::string key){
  return 0;
}

template<typename Comparator>
int CardShop::MergeSort(Comparator comp, std::string key){
  return 0;
}

