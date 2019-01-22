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

using namespace std;
zmq::context_t context(1);
zmq::socket_t publisher(context, ZMQ_PUB);
zmq::socket_t publisher_mine(context, ZMQ_PUB);

//---------------------------------------------------------
// Constructor

mine_distributor::mine_distributor()
{
  lock = 0;
  start = 0;
  delay = 0.00;
  delay_ga1 = 0.00;
  delay_qroute = 0.04;
  delay_ga2 = 0.06;
  pattern = "circle";

  // For Line
  ga1_init_x = 7.0;
  ga2_init_x = 140;
  ga1_final_x = 30.0;
  ga2_final_x = 160;
  qroute_area_init_x = 54;
  qroute_area_final_x = 108;

  // Circle
  radius = 10;
  circle_increment = 0;
  ga1_center_x = 17;
  ga1_center_y = -77;
  qroute_center_x = 79;
  qroute_center_y = -73;
  ga2_center_x = 147;
  ga2_center_y = -75;

  // no:of mines and label
  count = 100;
  mine_count = 0;
  total_mines = 50;
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


bool mine_distributor::Line_pattern(double duration)
{

  if (duration > delay_ga1 && lock == 0)
  {
    double y = -0.8 * ga1_init_x -500/7;
    string content = "x=" +std::to_string(ga1_init_x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher,"M");
    s_send(publisher,content);

    string content_add = "hazard = x=" +std::to_string(ga1_init_x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher_mine,"M");
    s_send(publisher_mine,content_add);

    count ++;
    ga1_init_x += 5;
    if (ga1_init_x >= ga1_final_x )
      lock = 1;

      // for statistical learning data
    std::ofstream outfile;
    outfile.open("mines_ga1.csv", std::ios_base::app);
    outfile << std::to_string(count) + "," + std::to_string(ga1_init_x) + "," + std::to_string(y) << "\n" ;
    outfile.close();

  }
  else if (duration > delay_qroute && lock == 1)
  {
    int y = 0.8 * qroute_area_init_x - 1000/7;
    string content = "x=" +std::to_string(qroute_area_init_x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher,"M");
    s_send(publisher,content);

    string content_add = "hazard = x=" +std::to_string(qroute_area_init_x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher_mine,"M");
    s_send(publisher_mine,content_add);

    count ++;
    qroute_area_init_x += 5;
    if (qroute_area_init_x >= qroute_area_final_x)
      lock = 2;

      // for statistical learning data
      std::ofstream outfile;
      outfile.open("mines_qroute.csv", std::ios_base::app);
      outfile << std::to_string(count) + "," + std::to_string(qroute_area_init_x) + "," + std::to_string(y) << "\n" ;
      outfile.close();

  }
  else if (duration > delay_ga2 && lock == 2)
  {
    int y = -0.8 * ga2_init_x + 200/7;
    string content = "x=" +std::to_string(ga2_init_x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher,"M");
    s_send(publisher,content);

    string content_add = "hazard = x=" +std::to_string(ga2_init_x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
    s_sendmore(publisher_mine,"M");
    s_send(publisher_mine,content_add);

    count ++;
    ga2_init_x += 5;
    if (ga2_init_x >= ga2_final_x )
      lock = 3;

    // for statistical learning data
    std::ofstream outfile;
    outfile.open("mines_ga2.csv", std::ios_base::app);
    outfile << std::to_string(count) + "," + std::to_string(ga2_init_x) + "," + std::to_string(y) << "\n" ;
    outfile.close();
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

    string content_add = "hazard = x=" +std::to_string(x)+ ",y=" +std::to_string(y)+ ",label= "+std::to_string(count)+", type=hazard";
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
      Line_pattern(duration);
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
