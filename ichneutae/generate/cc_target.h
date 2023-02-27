#ifndef ICHNEUTAE_GENERATE_CC_TARGET_H
#define ICHNEUTAE_GENERATE_CC_TARGET_H

namespace in::generate {
/// cc_target defines the different generation targets available for the cc generators
enum class cc_target {
	unknown = 0,
	library = 1,
	binary = 2,
};
} // namespace in::generate

#endif // ICHNEUTAE_GENERATE_CC_TARGET_H
