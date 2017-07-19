/* a lot of times we need to compute a rolling n point average. All that is requried is to add the new sample point and remove the oldest sample point. 
 *
 *      average = old_average + (new_sample_point/num) - (old_sample_point)/num; 
 *
 the alternative is to compute block average which only averages every n samples. It adds the samples from 0 to n. this works as long as the granularity at which the average has to be sampled is nottoo small. 
*/ 
#include <cstdint> 

struct sAve {
	int32_t blockAverage; 
	uint16_t numSamples;
};

int16_t AddSampleToAverage(struct sAve ave, int16_t newSample){
	ave.blockAverage += newSample; 
	ave.numSamples++;
}

int16_t GetAverage(struct sAve ave) {
	int16_t average = ave.blockAverage/ave.numSamples; // get ready for the next block
	ave.blockAverage = 0; ave.numSamples = 0;
	return average; 
}
