#include <rtm/Manager.h>
#include <rtm/NamingManager.h>
#include <rtm/CORBA_RTCUtil.h>
#include <iostream>


int main (int argc, char** argv)
{
  RTC::Manager* manager;
  manager = RTC::Manager::init(argc, argv);

  manager->activateManager();
  manager->runManager(true);

  RTC::RTObject_var consolein = RTC::RTObject::_nil();
  RTC::RTObject_var consoleout = RTC::RTObject::_nil();

  RTC::NamingManager* nm = RTC::Manager::instance().getNaming();
  RTC::RTCList consoleinlist = nm->string_to_component("rtcname://localhost:2809/*/ConsoleIn0");

  if (consoleinlist.length() > 0)
  {
    consolein = consoleinlist[0];
  }
  else
  {
    std::cout << "Could not found ConsoleIn0" << std::endl;
    return 1;
  }

  RTC::RTCList consoleoutlist = nm->string_to_component("rtcname://localhost:2809/*/ConsoleOut0");

  if (consoleoutlist.length() > 0)
  {
    consoleout = consoleoutlist[0];
  }
  else
  {
    std::cout << "Could not found ConsoleOut0" << std::endl;
    return 1;
  }
  /*
  RTC::PortService_var port_in_var = CORBA_RTCUtil::get_port_by_name(consoleout.in(), "ConsoleOut0.in");

  if (CORBA::is_nil(port_in_var))
  {
    std::cout << "Could not found ConsoleOut0.in" << std::endl;
    return 1;
  }

  RTC::PortService_var port_out_var = CORBA_RTCUtil::get_port_by_name(consolein.in(), "ConsoleIn0.out");

  if (CORBA::is_nil(port_out_var))
  {
    std::cout << "Could not found ConsoleIn0.out" << std::endl;
    return 1;
  }
  */

  RTC::PortService_var port_in_var = CORBA_RTCUtil::get_port_by_url("rtcname://localhost:2809/*/ConsoleOut0.in");

  if (CORBA::is_nil(port_in_var))
  {
    std::cout << "Could not found ConsoleOut0.in" << std::endl;
    return 1;
  }

  RTC::PortService_var port_out_var = CORBA_RTCUtil::get_port_by_url("rtcname://localhost:2809/*/ConsoleIn0.out");

  if (CORBA::is_nil(port_out_var))
  {
    std::cout << "Could not found ConsoleIn0.out" << std::endl;
    return 1;
  }

  coil::Properties prop;
  prop["dataport.dataflow_type"] = "push";
  prop["dataport.interface_type"] = "corba_cdr";
  prop["dataport.subscription_type"] = "new";
  //CORBA_RTCUtil::connect("test_connector", prop, port_in_var.in(), port_out_var.in());

  RTC::PortServiceList target_ports;
  target_ports.length(1);
  target_ports[0] = RTC::PortService::_duplicate(port_out_var.in());
  CORBA_RTCUtil::connect_multi("test_connector", prop, port_in_var.in(), target_ports);

  //CORBA_RTCUtil::disconnect_connector_name(port_in_var.in(), "test_connector");
  //CORBA_RTCUtil::disconnect_connector_name("rtcname://localhost:2809/*/ConsoleOut0.in", "test_connector");
  //CORBA_RTCUtil::disconnect_all(port_in_var.in());
  

  //CORBA_RTCUtil::activate(consolein.in(), 0);
  CORBA_RTCUtil::activate(consoleout.in());

  /*
  RTC::LifeCycleState state;
  CORBA_RTCUtil::get_state(state, consoleout.in(), 0);
  std::cout << state << std::endl;
  */

  if (CORBA_RTCUtil::is_in_inactive(consoleout.in()))
  {
    std::cout << "Inactive State" << std::endl;
  }
  else if (CORBA_RTCUtil::is_in_active(consoleout.in()))
  {
    std::cout << "Active State" << std::endl;
  }
  else if (CORBA_RTCUtil::is_in_error(consoleout.in()))
  {
    std::cout << "Error State" << std::endl;
  }

  CORBA_RTCUtil::set_default_rate(consoleout.in(), 20.0);
  std::cout << CORBA_RTCUtil::get_default_rate(consoleout.in()) << std::endl;

  CORBA_RTCUtil::set_current_rate(consoleout.in(), 0, 50.0);
  std::cout << CORBA_RTCUtil::get_current_rate(consoleout.in(), 0) << std::endl;

  //CORBA_RTCUtil::deactivate(consolein.in());
  CORBA_RTCUtil::deactivate(consoleout.in());

  CORBA_RTCUtil::add_rtc_to_default_ec(consoleout.in(), consolein.in());
  RTC::RTCList rtclist = CORBA_RTCUtil::get_participants_rtc(consoleout.in());
  for(CORBA::ULong i=0;i < rtclist.length();i++)
  {
    
    std::cout << i << "\t" << CORBA_RTCUtil::get_component_profile(rtclist[i].in()) << std::endl;
  }
  
  CORBA_RTCUtil::remove_rtc_to_default_ec(consoleout.in(), consolein.in());
  //CORBA_RTCUtil::reset(consolein.in());
  //CORBA_RTCUtil::reset(consoleout.in());

  


  RTC::RTObject_var configsample = RTC::RTObject::_nil();
  RTC::RTCList configsamplelist = nm->string_to_component("rtcname://localhost:2809/*/ConfigSample0");

  if (configsamplelist.length() > 0)
  {
    configsample = configsamplelist[0];
  }
  else
  {
    std::cout << "Could not found ConfigSample0" << std::endl;
    return 1;
  }

  CORBA_RTCUtil::set_active_configuration(configsample.in(), "int_param1", "100");

  CORBA_RTCUtil::set_configuration(configsample.in(), "mode0", "str_param1", "test");

  std::cout << CORBA_RTCUtil::get_active_configuration_name(configsample.in()) << std::endl;
  std::cout << CORBA_RTCUtil::get_active_configuration(configsample.in()) << std::endl;
  std::cout << CORBA_RTCUtil::get_configuration(configsample.in(), "mode1") << std::endl;
  std::cout << CORBA_RTCUtil::get_parameter_by_key(configsample.in(), "mode1", "int_param1") << std::endl;



  std::cout << CORBA_RTCUtil::get_component_profile(consolein.in()) << std::endl;

  coil::vstring portlist = CORBA_RTCUtil::get_port_names(consolein.in());
  for (auto& port : portlist)
  {
    std::cout << port << std::endl;
  }

  coil::vstring inportlist = CORBA_RTCUtil::get_inport_names(consoleout.in());
  for (auto& port : inportlist)
  {
    std::cout << port << std::endl;
  }

  coil::vstring outportlist = CORBA_RTCUtil::get_outport_names(consolein.in());
  for (auto& port : outportlist)
  {
    std::cout << port << std::endl;
  }

  RTC::RTObject_var myserviceprovider = RTC::RTObject::_nil();
  RTC::RTCList myserviceproviderlist = nm->string_to_component("rtcname://localhost:2809/*/MyServiceProvider0");

  if (myserviceproviderlist.length() > 0)
  {
    myserviceprovider = myserviceproviderlist[0];
  }
  else
  {
    std::cout << "Could not found MyServiceProvider0" << std::endl;
    return 1;
  }

  RTC::RTObject_var myserviceconsumer = RTC::RTObject::_nil();
  RTC::RTCList myserviceconsumerlist = nm->string_to_component("rtcname://localhost:2809/*/MyServiceConsumer0");

  if (myserviceconsumerlist.length() > 0)
  {
    myserviceconsumer = myserviceconsumerlist[0];
  }
  else
  {
    std::cout << "Could not found MyServiceConsumer0" << std::endl;
    return 1;
  }

  coil::vstring svcportlist = CORBA_RTCUtil::get_svcport_names(myserviceprovider.in());
  for (auto& port : svcportlist)
  {
    std::cout << port << std::endl;
  }

  coil::vstring inconlist = CORBA_RTCUtil::get_connector_names(port_in_var.in());
  for (auto& connector : inconlist)
  {
    std::cout << connector << std::endl;
  }

  coil::vstring outconlist = CORBA_RTCUtil::get_connector_names(consolein.in(), "ConsoleIn0.out");
  for (auto& connector : outconlist)
  {
    std::cout << connector << std::endl;
  }

  


  CORBA_RTCUtil::disconnect_all("rtcname://localhost:2809/*/ConsoleIn0.out");
  
  manager->terminate();
  manager->join();

  return 0;
}
