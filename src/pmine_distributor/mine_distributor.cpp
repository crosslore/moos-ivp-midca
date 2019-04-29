/************************************************************/
/*    NAME: Sravya Kondrakunta                                              */
/*    ORGN: MIT                                             */
/*    FILE: mine_distributor.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "mine_distributor.h"
#include "zhelpers.hpp"
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <string>
#include <time.h>
#include <cmath>
#include <chrono>
#include <thread>


using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
using namespace std;

zmq::context_t context(1);
zmq::socket_t publisher(context, ZMQ_PUB);
zmq::socket_t publisher_mine(context, ZMQ_PUB);

//---------------------------------------------------------
// Constructor

mine_distributor::mine_distributor()
{
  lock = 0;
  flag = 1;
  start = 0; // this is to record the initial time
  delay = 0.00;  // the delay at which the mines should start
  delay_ga1 = 0.01; // delay for the mines to be layed in ga1
  delay_qroute = 0.02; // delay for the mines to layed in qroute
  delay_ga2 = 0.03;   // delay for the mines to layed in qroute
  pattern = "circle";   // The pattern is line

  // For Line
  overflow_flag = 2; // to distribute mines across the specified interval
  line_increment = 10; // Distribute mines in an interval of 10



  // Circle
  radius = 15;
  circle_increment = 5;
  ga1_center_x = 17;
  ga1_center_y = -77;
  qroute_center_x = 79;
  qroute_center_y = -73;
  ga2_center_x = 147;
  ga2_center_y = -75;

  // no:of mines and label
  count = 100;  // label of the mines to begin with
  mine_count = 0;   // to count number of mines
  total_mines = 30; // The total number of mines to distribute




  if (pattern == "line")
    increment = 0; // to maintain the increments
  if (pattern == "circle")
    increment = 360/(total_mines/17) ;
}

//---------------------------------------------------------
// Destructor

mine_distributor::~mine_distributor()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool mine_distributor::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;

  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

#if 0 // Keep these around just for template
    string key   = msg.GetKey();
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
   }

   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool mine_distributor::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);

   RegisterVariables();
   return(true);
}


//------------------------------------------------------------------
// Procedure: Line_pattern()
//            Hazards in the format of a line


bool mine_distributor::Line_pattern(double duration, double ga1_init_x,
                                                     double ga1_final_x,
                                                     double ga2_init_x,
                                                     double ga2_final_x,
                                                     double qroute_area_init_x,
                                                     double qroute_area_final_x,
                                                     double slope,
                                                     double intercept)
{

  if (duration > delay_ga1 && lock == 0)
  {
    // if the mines are placed in the first interval go to second inter
    if (mine_count >= total_mines/3 )
    {
      lock = 1;
      increment = line_increment;
      overflow_flag = 2;
    }

    else if ((ga1_init_x + increment) >= ga1_final_x )
        {
        increment =  (line_increment/ overflow_flag)  ;
        overflow_flag = overflow_flag * 2;
        }
    //else if ( (ga1_init_x + increment) <= ga1_init_x )
    //  increment =  increment + 5 ;
   else
   {
     double y = slope * ( ga1_init_x + increment ) + intercept;
     string content = "x=" +std::to_string(ga1_init_x + increment )+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
     s_sendmore(publisher,"M");
     s_send(publisher,content);

     string content_add = "hazard = x=" +std::to_string(ga1_init_x + increment )+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+",type=hazard";
     s_sendmore(publisher_mine,"M");
     s_send(publisher_mine,content_add);

     // for statistical learning data
     std::ofstream outfile;
     outfile.open("mines_ga1.csv", std::ios_base::app);
     outfile << std::to_string(count) + "," + std::to_string(ga1_init_x + increment) + "," + std::to_string(y) << "\n" ;
     outfile.close();

     //std::ofstream outfile;
     outfile.open("mines_line.txt", std::ios_base::app);
     outfile  << content_add <<"\n" ;
     outfile.close();

     count ++;
     mine_count ++ ;

     increment += line_increment;
    }
}

  else if (duration > delay_qroute && lock == 1)
  {


    if (mine_count >= (2*total_mines/3) )
    {
      lock = 2;
      increment = line_increment;
      overflow_flag = 2;
    }
    else if ((qroute_area_init_x + increment) >= qroute_area_final_x )
    {
        increment =  (line_increment / overflow_flag) ;
        overflow_flag = overflow_flag * 2;
    }
   else
   {
     int y = slope * (qroute_area_init_x + increment ) + intercept;
     string content = "x=" +std::to_string(qroute_area_init_x + increment)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
     s_sendmore(publisher,"M");
     s_send(publisher,content);

     string content_add = "hazard = x=" +std::to_string(qroute_area_init_x + increment)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+",type=hazard";
     s_sendmore(publisher_mine,"M");
     s_send(publisher_mine,content_add);

     // for statistical learning data
     std::ofstream outfile;
     outfile.open("mines_qroute.csv", std::ios_base::app);
     outfile << std::to_string(count) + "," + std::to_string(qroute_area_init_x + increment) + "," + std::to_string(y) << "\n" ;
     outfile.close();

     //std::ofstream outfile;
     outfile.open("mines_line.txt", std::ios_base::app);
     outfile  << content_add <<"\n" ;
     outfile.close();

     count ++;
     mine_count ++ ;
    increment += line_increment;
    }
  }


  else if (duration > delay_ga2 && lock == 2)
  {

    if (mine_count >= total_mines )
    {
      lock = 3;
      increment = line_increment;
      overflow_flag = 2;
      mine_count = 0;
      return (false);
    }
    else if ((ga2_init_x + increment) >= ga2_final_x )
    {
        increment =  (line_increment/overflow_flag) ;
        overflow_flag = 2 * overflow_flag;
      }
    //else if ( (ga2_init_x + increment) <= ga2_init_x )
    //    increment += 5 ;
   else
   {

     int y = slope * (ga2_init_x + increment ) + intercept;
     string content = "x=" +std::to_string(ga2_init_x + increment)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
     s_sendmore(publisher,"M");
     s_send(publisher,content);

     string content_add = "hazard = x=" +std::to_string(ga2_init_x + increment)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+",type=hazard";
     s_sendmore(publisher_mine,"M");
     s_send(publisher_mine,content_add);

     // for statistical learning data
     std::ofstream outfile;
     outfile.open("mines_ga2.csv", std::ios_base::app);
     outfile << std::to_string(count) + "," + std::to_string(ga2_init_x + increment) + "," + std::to_string(y) << "\n" ;
     outfile.close();

     //std::ofstream outfile;
     outfile.open("mines_line.txt", std::ios_base::app);
     outfile  << content_add <<"\n" ;
     outfile.close();

     count ++;
     mine_count ++ ;
     increment += line_increment;
   }



  }

  else
  {
    return (true);
  }

  return (true);
}


//------------------------------------------------------------------
// Procedure: Circle_pattern()
//            Hazards in the format of a circle


bool mine_distributor::Circle_pattern(double duration)
{

  if (duration > delay_ga1 && lock == 0)
  {
    double x = radius * cos(circle_increment) + ga1_center_x ;
    double y = radius * sin(circle_increment) + ga1_center_y ;
    string content = "x=" +std::to_string(x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher,"M");
    s_send(publisher,content);

    string content_add = "hazard = x=" +std::to_string(x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher_mine,"M");
    s_send(publisher_mine,content_add);

    count ++;
    mine_count ++ ;
    circle_increment = circle_increment + increment;
    if (mine_count >= total_mines/3 )
    {
      lock = 1;
      circle_increment = 0;
    }

    // for statistical learning data
    std::ofstream outfile;
    outfile.open("mines_ga1.csv", std::ios_base::app);
    outfile << std::to_string(count) + "," + std::to_string(x) + "," + std::to_string(y) << "\n" ;
    outfile.close();
  }
  else if (duration > delay_qroute && lock == 1)
  {
    double x = radius * cos(circle_increment) + qroute_center_x ;
    double y = radius * sin(circle_increment) + qroute_center_y ;
    string content = "x=" +std::to_string(x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher,"M");
    s_send(publisher,content);

    string content_add = "hazard = x=" +std::to_string(x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+",type=hazard";
    s_sendmore(publisher_mine,"M");
    s_send(publisher_mine,content_add);

    count ++;
    mine_count ++ ;
    circle_increment = circle_increment + increment;
    if (mine_count >= (2*total_mines)/3 )
    {
      lock = 2;
      circle_increment = 0;
    }

    // for statistical learning data
    std::ofstream outfile;
    outfile.open("mines_qroute.csv", std::ios_base::app);
    outfile << std::to_string(count) + "," + std::to_string(x) + "," + std::to_string(y) << "\n" ;
    outfile.close();

    //std::ofstream outfile;
    outfile.open("mines_line.txt", std::ios_base::app);
    outfile  << content_add <<"\n" ;
    outfile.close();
  }
  else if (duration > delay_ga2 && lock == 2)
  {
    double x = radius * cos(circle_increment) + ga2_center_x ;
    double y = radius * sin(circle_increment) + ga2_center_y ;
    string content = "x=" +std::to_string(x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher,"M");
    s_send(publisher,content);

    string content_add = "hazard = x=" +std::to_string(x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher_mine,"M");
    s_send(publisher_mine,content_add);

    count ++;
    mine_count ++ ;
    circle_increment = circle_increment + increment;
    if (mine_count >= total_mines )
    {
      lock = 3;
      circle_increment = 0;
    }
    std::ofstream outfile;
    outfile.open("mines_ga2.csv", std::ios_base::app);
    outfile << std::to_string(count) + "," + std::to_string(x) + "," + std::to_string(y) << "\n" ;
    outfile.close();
  }
  else
  {
    return (true);
  }


  return (true);
}




//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool mine_distributor::Iterate()
{
  double duration;
  duration = double( clock() - start ) / (double) CLOCKS_PER_SEC;

  cout << duration << "\n" ;

  if (pattern == "line")
  {
      // For the first line
      /*
      // For Line
      slope = 0.7;
      intercept = -104.7;
      ga1_init_x = -50.0;
      ga2_init_x = 132;
      ga1_final_x = 37.0;
      ga2_final_x = 165;
      qroute_area_init_x = 52;
      qroute_area_final_x = 120;
      overflow_flag = 2;
      */
      if (flag == 1)
      {
      if (!Line_pattern(duration, 6, 20.0, 32, 36, 23, 30, 0.7,-100.7))
        {
          flag = 2;
          lock = 0;
        }
      }
      else if (flag == 2)
      {
        if (!Line_pattern(duration, 65.0, 80.0, 100, 120, 85, 100, 0.7,-140.5))
          {

            flag = 3;
            lock = 0;
          }
      }

      else if (flag == 3)
      {
        total_mines = 10;
        if (!Line_pattern(duration, 136.0, 150.0, 157, 162, 153, 156, 0.7,-190))
          {
            flag = 4;
            lock = 0;
          }
      }

      else if (flag == 4)
      {
        total_mines = 10;
        if (!Line_pattern(duration, 0.0, 20.0, 70, 100, 40, 60, 0.7,10))
          {
            flag = 5;
            lock = 0;
          }
      }
      else
      {
        return (true);
      }

  }
  else if (pattern == "circle")
      Circle_pattern(duration);

  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool mine_distributor::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = stripBlankEnds(*p);

      if(param == "FOO") {
        //handled
      }
      else if(param == "BAR") {
        //handled
      }
    }
  }
  start = clock();
  publisher.connect("tcp://127.0.0.1:5505");
  publisher_mine.bind("tcp://127.0.0.1:5522");
  int timeout = 1;
  int count = 2;
  publisher.setsockopt (ZMQ_SNDHWM, &count, sizeof (int));
  publisher_mine.setsockopt (ZMQ_SNDHWM, &count, sizeof (int));
  RegisterVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void mine_distributor::RegisterVariables()
{
  // Register("FOOBAR", 0);
}
