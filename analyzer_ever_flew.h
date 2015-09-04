#ifndef ANALYZE_EVER_FLEW_H
#define ANALYZE_EVER_FLEW_H

/*
 * analyze_ever_flew
 *
 */

#include "analyzer.h"
#include "analyzervehicle_copter.h"

class Analyzer_Ever_Flew : public Analyzer {
public:
    Analyzer_Ever_Flew(int fd, struct sockaddr_in *sa, AnalyzerVehicle::Base *&vehicle) :
	Analyzer(fd, sa, vehicle)
    { }

    const char *name() const { return "Ever Flew"; }
    const char *description() const {
        return "This test will FAIL if the craft did not ever seem to fly";
    }

    void handle_decoded_message(uint64_t T, mavlink_heartbeat_t &hearbeat) override;
    void handle_decoded_message(uint64_t T, mavlink_servo_output_raw_t &servos) override;

    void results_json_results(Json::Value&);
private:
    bool ever_armed = false;
    bool servos_past_threshold = false;
    uint64_t pass_timestamp = 0;

    void evaluate(uint64_t T);
};

#endif
