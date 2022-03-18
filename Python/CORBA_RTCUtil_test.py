#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys

import OpenRTM_aist
import OpenRTM_aist.CORBA_RTCUtil
from omniORB import CORBA


def main():
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.activateManager()
    mgr.runManager(True)

    #consolein = None
    #consoleout = None
    nm = OpenRTM_aist.Manager.instance().getNaming()
    consoleinlist = nm.string_to_component(
        "rtcname://localhost:2809/*/ConsoleIn0")

    if consoleinlist:
        consolein = consoleinlist[0]
    else:
        print("Could not found ConsoleIn0")
        sys.exit(1)

    consoleoutlist = nm.string_to_component(
        "rtcname://localhost:2809/*/ConsoleOut0")
    if consoleoutlist:
        consoleout = consoleoutlist[0]
    else:
        print("Could not found ConsoleOut0")
        sys.exit(1)

    configsamplelist = nm.string_to_component(
        "rtcname://localhost:2809/*/ConfigSample0")
    if configsamplelist:
        configsample = configsamplelist[0]
    else:
        print("Could not found ConfigSample0")
        sys.exit(1)

    myserviceproviderlist = nm.string_to_component(
        "rtcname://localhost:2809/*/MyServiceProvider0")
    if myserviceproviderlist:
        myserviceprovider = myserviceproviderlist[0]
    else:
        print("Could not found MyServiceProvider0")
        sys.exit(1)

    myserviceconsumerlist = nm.string_to_component(
        "rtcname://localhost:2809/*/ConsoleOut0")
    if myserviceconsumerlist:
        myserviceconsumer = myserviceconsumerlist[0]
    else:
        print("Could not found ConsoleOut0")
        sys.exit(1)
    """
    port_in_var = OpenRTM_aist.CORBA_RTCUtil.get_port_by_name(
        consoleout, "ConsoleOut0.in")
    if CORBA.is_nil(port_in_var):
        print("Could not found ConsoleOut0.in")
        sys.exit(1)

    port_out_var = OpenRTM_aist.CORBA_RTCUtil.get_port_by_name(
        consolein, "ConsoleIn0.out")
    if CORBA.is_nil(port_out_var):
        print("Could not found ConsoleOut0.in")
        sys.exit(1)
    """
    port_in_var = OpenRTM_aist.CORBA_RTCUtil.get_port_by_url(
        "rtcname://localhost:2809/*/ConsoleOut0.in")
    if CORBA.is_nil(port_in_var):
        print("Could not found ConsoleOut0.in")
        sys.exit(1)

    port_out_var = OpenRTM_aist.CORBA_RTCUtil.get_port_by_url(
        "rtcname://localhost:2809/*/ConsoleIn0.out")
    if CORBA.is_nil(port_out_var):
        print("Could not found ConsoleOut0.in")
        sys.exit(1)

    prop = OpenRTM_aist.Properties()
    prop.setProperty("dataport.dataflow_type", "push")
    prop.setProperty("dataport.interface_type", "corba_cdr")
    prop.setProperty("dataport.subscription_type", "new")
    # OpenRTM_aist.CORBA_RTCUtil.connect(
    #    "test_connector", prop, port_in_var, port_out_var)

    OpenRTM_aist.CORBA_RTCUtil.connect_multi(
        "test_connector", prop, port_in_var, [port_out_var])

    OpenRTM_aist.CORBA_RTCUtil.activate(consoleout, 0)
    #OpenRTM_aist.CORBA_RTCUtil.activate(consolein, 0)

    ret, state = OpenRTM_aist.CORBA_RTCUtil.get_state(consoleout, 0)
    print(state)

    if OpenRTM_aist.CORBA_RTCUtil.is_in_inactive(consoleout):
        print("Inactive State")
    elif OpenRTM_aist.CORBA_RTCUtil.is_in_active(consoleout):
        print("Active State")
    elif OpenRTM_aist.CORBA_RTCUtil.is_in_error(consoleout):
        print("Error State")

    OpenRTM_aist.CORBA_RTCUtil.deactivate(consoleout, 0)
    #OpenRTM_aist.CORBA_RTCUtil.deactivate(consolein, 0)

    #OpenRTM_aist.CORBA_RTCUtil.reset(consoleout, 0)
    #OpenRTM_aist.CORBA_RTCUtil.reset(consolein, 0)

    # OpenRTM_aist.CORBA_RTCUtil.disconnect_by_portref_connector_name(
    #    port_in_var, "test_connector")

    # OpenRTM_aist.CORBA_RTCUtil.disconnect_by_portname_connector_name(
    #    "rtcname://localhost:2809/*/ConsoleOut0.in", "test_connector")
    # OpenRTM_aist.CORBA_RTCUtil.disconnect_all_by_ref(port_in_var)

    #OpenRTM_aist.CORBA_RTCUtil.set_default_rate(consoleout, 20.0)
    # print(OpenRTM_aist.CORBA_RTCUtil.get_default_rate(consoleout))
    #OpenRTM_aist.CORBA_RTCUtil.set_current_rate(consoleout, 0, 50.0)
    #print(OpenRTM_aist.CORBA_RTCUtil.get_current_rate(consoleout, 0))

    OpenRTM_aist.CORBA_RTCUtil.add_rtc_to_default_ec(consoleout, consolein)

    i = 0
    for rtc in OpenRTM_aist.CORBA_RTCUtil.get_participants_rtc(consoleout):
        print(i, OpenRTM_aist.CORBA_RTCUtil.get_component_profile(rtc))
        i += 1

    OpenRTM_aist.CORBA_RTCUtil.remove_rtc_to_default_ec(consoleout, consolein)

    OpenRTM_aist.CORBA_RTCUtil.set_active_configuration(
        configsample, "int_param1", "100")

    OpenRTM_aist.CORBA_RTCUtil.set_configuration(
        configsample, "mode0", "str_param1", "test")

    print(OpenRTM_aist.CORBA_RTCUtil.get_active_configuration_name(configsample))

    print(OpenRTM_aist.CORBA_RTCUtil.get_active_configuration(configsample))

    print(OpenRTM_aist.CORBA_RTCUtil.get_configuration(configsample, "mode1"))

    print(OpenRTM_aist.CORBA_RTCUtil.get_parameter_by_key(
        configsample, "mode1", "int_param1"))

    print(OpenRTM_aist.CORBA_RTCUtil.get_component_profile(consolein))

    for port in OpenRTM_aist.CORBA_RTCUtil.get_port_names(consolein):
        print(port)
    for port in OpenRTM_aist.CORBA_RTCUtil.get_inport_names(consoleout):
        print(port)
    for port in OpenRTM_aist.CORBA_RTCUtil.get_outport_names(consolein):
        print(port)
    for port in OpenRTM_aist.CORBA_RTCUtil.get_svcport_names(myserviceprovider):
        print(port)

    for connector in OpenRTM_aist.CORBA_RTCUtil.get_connector_names_by_portref(port_in_var):
        print(connector)

    for connector in OpenRTM_aist.CORBA_RTCUtil.get_connector_names(consolein, "ConsoleIn0.out"):
        print(connector)

    OpenRTM_aist.CORBA_RTCUtil.disconnect_all_by_name(
        "rtcname://localhost:2809/*/ConsoleIn0.out")

    mgr.shutdown()


if __name__ == "__main__":
    main()
