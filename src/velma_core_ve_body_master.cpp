// Copyright 2014 WUT
/*
 * velma_service.cpp
 *
 *  Created on: 17 lut 2014
 *      Author: Konrad Banachowicz
 */

#include <rtt/plugin/ServicePlugin.hpp>

#include "common_behavior/master_service.h"
#include "velma_core_cs_ve_body_msgs/Command.h"
#include "velma_core_ve_body_re_body_msgs/Status.h"
#include "input_data.h"

namespace velma_core_ve_body_types {

class VelmaCoreVeBodyMaster : public common_behavior::MasterService {
public:
    explicit VelmaCoreVeBodyMaster(RTT::TaskContext* owner) :
        common_behavior::MasterService(owner),
        port_cmd_in_("command_INPORT"),
        port_status_in_("status_INPORT")
    {
        owner->addPort(port_cmd_in_);
        owner->addPort(port_status_in_);
    }

    virtual ~VelmaCoreVeBodyMaster() {
    }

    virtual void readPorts(boost::shared_ptr<common_behavior::InputData >& in_data) {
        boost::shared_ptr<InputData > in = boost::static_pointer_cast<InputData >(in_data);
        port_cmd_in_.read(in->cmd_);
        port_status_in_.read(in->status_);
    }

    virtual boost::shared_ptr<common_behavior::InputData > getDataSample() {
        boost::shared_ptr<InputData > ptr(new InputData());
        ptr->cmd_ = velma_core_cs_ve_body_msgs::Command();
        ptr->status_ = velma_core_ve_body_re_body_msgs::Status();
        return boost::static_pointer_cast<common_behavior::InputData >( ptr );
    }

private:
    RTT::InputPort<velma_core_cs_ve_body_msgs::Command > port_cmd_in_;
    RTT::InputPort<velma_core_ve_body_re_body_msgs::Status > port_status_in_;
};

};  // namespace velma_core_ve_body_types

ORO_SERVICE_NAMED_PLUGIN(velma_core_ve_body_types::VelmaCoreVeBodyMaster, "VelmaCoreVeBodyMaster");

