# become cool
cd ~/devstack
. openrc admin admin

# create the necessary image:

glance image-create --name "Cirros 0.3.3" --disk-format qcow2 --container-format bare --is-public True --copy http://download.cirros-cloud.net/0.3.3/cirros-0.3.3-x86_64-disk.img

# create the necessary network

neutron net-create internal001; neutron subnet-create --name internal001 internal001 192.168.200.0/24

# create the stack

cd ~/custom-templates

heat stack-create stackname -e env.yaml -f simple.yaml
