./build.sh

cp unittests/sample_data_model.aml out/linux/x86_64/release/unittests/
cd out/linux/x86_64/release/unittests
./ezmqx_config_test
./ezmqx_publisher_test
./ezmqx_subscriber_test
./ezmqx_topicdiscovery_test
./ezmqx_topicvalidate_test