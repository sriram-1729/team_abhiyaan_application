#include<bits/stdc++.h>
using namespace std;

class Publisher
{
public:
  struct Node
  {
    std::string name;
    std::string topic;
    std::string published_string;
    int publishing_mode;
    Node* next;
  };

  Node* head;
  Node* tail;
  int size;

  Publisher()
  {
    head = NULL;
    tail = NULL;
    size = 0;
  }

  void addPublisher()
  {
    Node* new_node = new Node();

    std::cout << "Enter the name of the publisher: ";
    getline(cin, new_node->name);
    std::cout << "Enter the topic to be published: ";
    getline(cin, new_node->topic);
    std::cout << "Enter the string to be published: ";
    getline(cin, new_node->published_string);
    new_node->publishing_mode = 0;
    
    if(size == 0)
      {
	head = new_node;
	tail = new_node;
	new_node->next = NULL;
	size++;
      }
    else
      {
	tail->next = new_node;
	tail = new_node;
	tail->next = NULL;
	size++;
      }
  }
  
  void listAllPublishers()
  {
    Node* curr = new Node();
    for(curr = head; curr != NULL; curr = curr->next)
      {
	std::cout << "Name of the publisher: " << curr->name << std::endl;
	std::cout << "Topic: " << curr->topic << std::endl;
	std::cout << "Published string: " << curr->published_string << std::endl;
	std::cout << "Publishing mode: " << curr->publishing_mode << std::endl;
	std::cout << std::endl;
      }
  }
  
  std::string showTopic (std::string name)
  {
    Node* curr = new Node();
    for(curr = head; curr != NULL; curr = curr->next)
      if (curr->name.compare(name) == 0)
	return curr->topic;
  }

  std::string showPublishedString(std::string name)
  {
    Node* curr = new Node();
    for(curr = head; curr!= NULL; curr = curr->next)
      if(curr->name.compare(name) == 0)
	return curr->published_string;
  }

  void changeMode(std::string name)
  {
    Node* curr = new Node();
    for(curr = head; curr != NULL; curr = curr->next)
      if (curr->name.compare(name) == 0)
	{
	  if(curr->publishing_mode == 0)
	    {
	      curr->publishing_mode = 1;
	      std::cout << "Publisher mode changed from 0 to 1" << std::endl;
	      break;
	    }
	  else
	    {
	      curr->publishing_mode = 0;
	      std::cout << "Publisher mode changed from 1 to 0" << std::endl;
	      break;
	    }
	}
  }
  
};

class Subscriber
{
public:
  struct Node
  {
    std::string name;
    std::string topic;
    std::string subscribed_string;
    int subscribing_mode;
    Node* next;
  };

  Node* head;
  Node* tail;
  int size;

  Subscriber()
  {
    head = NULL;
    tail = NULL;
    size = 0;
  }

  void addSubscriber()
  {
    Node* new_node = new Node();

    std::cout << "Enter the name of the subscriber: ";
    getline(cin, new_node->name);
    std::cout << "Enter the topic to be subscribed to: ";
    getline(cin, new_node->topic);
    new_node->subscribing_mode = 0;
    
    if(size == 0)
      {
	head = new_node;
	tail = new_node;
	new_node->next = NULL;
	size++;
      }
    else
      {
	tail->next = new_node;
	tail = new_node;
	tail->next = NULL;
	size++;
      }
  }

  void listAllSubscribers()
  {
    Node* curr = new Node();
    for(curr = head; curr != NULL; curr = curr->next)
      {
	std::cout << "Name of the subscriber: " << curr->name << std::endl;
	std::cout << "Topic: " << curr->topic << std::endl;
	if(curr->subscribing_mode == 0)
	  std::cout << "Subscribing mode: " << curr->subscribing_mode << std::endl;
	else
	  {
	    std::cout << "Subscribed string: " << curr->subscribed_string << std::endl;
	    std::cout << "Subscribing mode: " << curr->subscribing_mode << std::endl;
	  }
	std::cout << std::endl;
      }
  }

  void storePublishedString(std::string topic, std::string published_string)
  {
    Node* curr = new Node();
    for(curr = head; curr!= NULL; curr = curr->next)
      if(curr->topic.compare(topic) == 0)
	{
	  curr->subscribed_string = published_string;
	  curr->subscribing_mode = 1;
	  std::cout << "Node " << curr->name << " subscribed to topic " << topic << "." << std::endl;
	}
  }
  
};

class Master
{
public:
  Publisher pub;
  Subscriber sub;
  
  void initiate()
  {
    std::string name;
    std::cout << "Enter the name of the publisher: ";
    getline(cin, name);
    pub.changeMode(name);
    std::string topic = pub.showTopic(name);
    std::string published_string = pub.showPublishedString(name);

    sub.storePublishedString(topic, published_string);
  }
    
};

int main()
{
  Master mas;

  while(1)
    {
      int t;
      std::cout << "Enter an option: ";
      std::cin >> t;
      std::cin.ignore();

      switch(t)
	{
	case 0:
	  break;
	case 1:
	  mas.pub.addPublisher();
	  break;
	case 2:
	  mas.sub.addSubscriber();
	  break;
	case 3:
	  mas.pub.listAllPublishers();
	  break;
	case 4:
	  mas.sub.listAllSubscribers();
	  break;
	case 5:mas.initiate();
	  break;
	default:
	  std::cout << "Invalid option selected." << std::endl;
	  break;
	}
      
      std::cout << "Operation successful!" << std::endl;

      if(t == 0)
	break;
    }

  return 0;
 }
