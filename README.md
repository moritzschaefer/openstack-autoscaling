# Scenario

Autoscaling openstack instances dependent on demand

# Motivation

For stakeholders it is cheaper to just buy ressources when needed and free them when not needed.
For the user it is convenient if there are enough instances for the requested service always (as well on high load), to not have to wait for the service.

# Problem

We don't know when we have to scale up or down. That means our cloud might be surprised to be tackled by a lot of requests at once when there are only few instance up and running. Reacting on this might and bringing up new instances might take some minutes which means, that in that time, the requesting users would suffer from bad performance and high delays.
To overcome this issue, the idea is to bring up instances based on the knowledge of earlier times (e.g. the last week). As an example, if we know that we had a peak of requests on monday from 14:00 to 15:00 we could use this knowledge to bring up enough instances on the next monday to handle that peak.
The premise here is that the number of requests(that hit the server) over time resembles a periodic function (with deviations of course). 

# Measurments/Simulations/Learning

For generating different loads we use Poisson distribution with a period of 30 seconds.

http://docs.scipy.org/doc/scipy-0.15.1/reference/generated/scipy.stats.poisson.html
http://www.gnu.org/software/gsl/manual/html_node/The-Poisson-Distribution.html

Justify 30 seconds.
Justify poisson.

Run make to compile the poisson generator

# Setup

sudo apt-get install libgsl0-dev
To bring up the test dev env, do the following steps

- Create a Ubuntu(!!) VM
- Get devstack (e.g. git)
- change /opt/stack/ceilometer/etc/pipeline.conf and change the periods to a shorter time (easier for testing, 30 seconds is good)
- run stack.sh to build the openstack environment


# Dev notes 

- Alarm period should be higher than the other periods
- Use something like this: 
matching_metadata: {'metadata.user_metadata.stack': {get_param: "OS::stack_id"}}
  Note. This is not working yet


# Todos

- Use poisson to emulate CPU load

- Fix cpu_util in ceilometer (is ~25% should be ~100%): https://bugs.launchpad.net/ceilometer/+bug/1421584
- For Ceilometer Alarm add the metadata parameter to just take values related to the given stack
