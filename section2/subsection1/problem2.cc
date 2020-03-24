/************************************************************
 *In this program, the master class contains two linked lists
 *containing the details of the publishers and subscribers.
 *When a new publisher/subscriber is created, it is added to
 *the corresponding linked list. Each node of the linked list
 *has the name, topic subscribed to/ publishing to,
 *published/subscribed string and the publishing/subscribing
 *mode (it determines whether the publisher/subscriber is
 *actively publishing/subscribing or not).
 *
 *When the program is initiated, the initial input to be
 *given is am integer, ranging from 0 to 5.
 *0 - Terminates the program.
 *1 - Adds a publisher to the publisher linked list.
 *2 - Adds a subscriber to the subscriber linked list.
 *3 - Lists all the publishers.
 *4 - Lists all the subscribers.
 *5 - Activates the given publisher and makes sure that
 *all the nodes subscribed to the topic the publisher publishs
 *to are activated.
 *
 *Assumptions:
 *A publisher can only publish to one topic.
 *A subscriber can only subscribe to one topic.
 *Deactivating a node is not possible.
 *Publishers/subscribers cannot be removed from their
 *respective linked lists.
 *The string to be published by a publisher cannot be changed
 *once the publisher is added to the linked list.
 *When Master is called, it is assumed that there is atleast
 *one subscriber in the subscriber linked list which
 *subscribes to the topic the publisher (which was sent to
 *Master) publishes to.
 ************************************************************/
#include<bits/stdc++.h>

namespace elementary_roscore
{
  
  class Publisher
  {
  private:
    struct Node
    {
      std::string name_;
      std::string topic_;
      std::string published_string_;
      int publishing_mode_;
      Node* next_;
    };

  public:
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
      std::getline(std::cin, new_node->name_);
      std::cout << "Enter the topic to be published: ";
      std::getline(std::cin, new_node->topic_);
      std::cout << "Enter the string to be published: ";
      std::getline(std::cin, new_node->published_string_);
      new_node->publishing_mode_ = 0;
    
      if(size == 0)
	{
	  head = new_node;
	  tail = new_node;
	  new_node->next_ = NULL;
	  size++;
	}
      else
	{
	  tail->next_ = new_node;
	  tail = new_node;
	  tail->next_ = NULL;
	  size++;
	}
    }
  
    void listAllPublishers()
    {
      Node* curr = new Node();
      for(curr = head; curr != NULL; curr = curr->next_)
	{
	  std::cout << "Name of the publisher: " << curr->name_ << std::endl;
	  std::cout << "Topic: " << curr->topic_ << std::endl;
	  std::cout << "Published string: " << curr->published_string_ << std::endl;
	  std::cout << "Publishing mode: " << curr->publishing_mode_ << std::endl;
	  std::cout << std::endl;
	}
    }
  
    std::string showTopic (std::string name)
    {
      Node* curr = new Node();
      for(curr = head; curr != NULL; curr = curr->next_)
	if (curr->name_.compare(name) == 0)
	  return curr->topic_;
    }

    std::string showPublishedString(std::string name)
    {
      Node* curr = new Node();
      for(curr = head; curr!= NULL; curr = curr->next_)
	if(curr->name_.compare(name) == 0)
	  return curr->published_string_;
    }

    void changeMode(std::string name)
    {
      Node* curr = new Node();
      for(curr = head; curr != NULL; curr = curr->next_)
	if (curr->name_.compare(name) == 0)
	  {
	    if(curr->publishing_mode_ == 0)
	      {
		curr->publishing_mode_ = 1;
		std::cout << "Publisher mode changed from 0 to 1" << std::endl;
		break;
	      }
	    else
	      {
		curr->publishing_mode_ = 0;
		std::cout << "Publisher mode changed from 1 to 0" << std::endl;
		break;
	      }
	  }
    }
  
  };

  class Subscriber
  {
  private:
    struct Node
    {
      std::string name_;
      std::string topic_;
      std::string subscribed_string_;
      int subscribing_mode_;
      Node* next_;
    };

  public:
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
      std::getline(std::cin, new_node->name_);
      std::cout << "Enter the topic to be subscribed to: ";
      std::getline(std::cin, new_node->topic_);
      new_node->subscribing_mode_ = 0;
    
      if(size == 0)
	{
	  head = new_node;
	  tail = new_node;
	  new_node->next_ = NULL;
	  size++;
	}
      else
	{
	  tail->next_ = new_node;
	  tail = new_node;
	  tail->next_ = NULL;
	  size++;
	}
    }

    void listAllSubscribers()
    {
      Node* curr = new Node();
      for(curr = head; curr != NULL; curr = curr->next_)
	{
	  std::cout << "Name of the subscriber: " << curr->name_ << std::endl;
	  std::cout << "Topic: " << curr->topic_ << std::endl;
	  if(curr->subscribing_mode_ == 0)
	    std::cout << "Subscribing mode: " << curr->subscribing_mode_ << std::endl;
	  else
	    {
	      std::cout << "Subscribed string: " << curr->subscribed_string_ << std::endl;
	      std::cout << "Subscribing mode: " << curr->subscribing_mode_ << std::endl;
	    }
	  std::cout << std::endl;
	}
    }

    void storePublishedString(std::string topic, std::string published_string)
    {
      Node* curr = new Node();
      for(curr = head; curr!= NULL; curr = curr->next_)
	if(curr->topic_.compare(topic) == 0)
	  {
	    curr->subscribed_string_ = published_string;
	    curr->subscribing_mode_ = 1;
	    std::cout << "Node " << curr->name_ << " subscribed to topic " << topic << "." << std::endl;
	  }
    }
  
  };

  class Master
  {
  public:
    Publisher pub;
    Subscriber sub;
    /************************************************************
     *void initiate():
     *Makes the specified publisher class publish to its topic.
     *Also makes sure that all the node subscribed to that topic
     *are activated and receive input from the publisher.
     ************************************************************/  
    void initiate()
    {
      std::string name;
      std::cout << "Enter the name of the publisher: ";
      std::getline(std::cin, name);
      pub.changeMode(name);
      std::string topic = pub.showTopic(name);
      std::string published_string = pub.showPublishedString(name);

      sub.storePublishedString(topic, published_string);
    }
    
  };

}// namespace elementary_roscore

int main()
{
  elementary_roscore::Master mas;

  int t = 1;

  while(t)
    {
      std::cout << "Enter an option: ";
      std::cin >> t;
/************************************************************
 *The purpose of std::cin.ignore() is explained in this
 *Stack Overflow post:
 *https://stackoverflow.com/questions/32309069/getline-and-
 *cin-used-one-after-another-skips-next-inputs
 ************************************************************/
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
	case 5:
	  mas.initiate();
	  break;
	default:
	  std::cout << "Invalid option selected." << std::endl << std::endl;
	  break;
	}
      
      if((t >= 0) && (t < 6))
	std::cout << "Operation successful!" << std::endl << std::endl;
    }

  return 0;
}
