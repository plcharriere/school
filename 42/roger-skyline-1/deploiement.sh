#!/bin/sh

echo "Mise à jour des sources de package..."
apt-get update -y > /dev/null
echo "Mise à jour des packages..."
apt-get upgrade -y > /dev/null
echo "Installation de sudo..."
apt-get install -y sudo > /dev/null
echo "Ajout de 'pcharrie' aux sudoers..."
usermod -aG sudo pcharrie

echo "Configuration de l'ip statique..."
echo "source /etc/network/interfaces.d/*" > /etc/network/interfaces
echo "auto lo" >> /etc/network/interfaces
echo "iface lo inet loopback" >> /etc/network/interfaces
echo "allow-hotplug enp0s3" >> /etc/network/interfaces
echo "iface enp0s3 inet static" >> /etc/network/interfaces
echo "	address 10.13.42.21" >> /etc/network/interfaces
echo "	netmask 255.255.255.252" >> /etc/network/interfaces
echo "	gateway 10.13.254.254" >> /etc/network/interfaces
ifdown enp0s3 > /dev/null 2>&1
ifup enp0s3 > /dev/null 2>&1

echo "Configuration du service SSH..."
echo "Port 42" >> /etc/ssh/sshd_config
echo "PermitRootLogin no" >> /etc/ssh/sshd_config
echo "PubKeyAuthentication yes" >> /etc/ssh/sshd_config
echo "PasswordAuthentication no" >> /etc/ssh/sshd_config
systemctl restart sshd

echo "Configuration du pare-feu..."
echo "#!/bin/sh" > /root/firewall.sh
echo "iptables -P INPUT DROP" >> /root/firewall.sh
echo "iptables -A INPUT -i lo -j ACCEPT" >> /root/firewall.sh
echo "iptables -A INPUT -p icmp -j ACCEPT" >> /root/firewall.sh
echo "iptables -A INPUT -m state --state ESTABLISHED -j ACCEPT" >> /root/firewall.sh
echo "iptables -A INPUT -p tcp --dport 42 -m limit --limit 30/second -j ACCEPT" >> /root/firewall.sh
echo "iptables -A INPUT -p tcp --dport 80 -m limit --limit 5/second -j ACCEPT" >> /root/firewall.sh
echo "iptables -A INPUT -p tcp --dport 443 -m limit --limit 5/second -j ACCEPT" >> /root/firewall.sh
echo "@reboot		root	sh /root/firewall.sh" >> /etc/crontab
systemctl restart cron
sh /root/firewall.sh

echo "Installation de portsentry..."
export DEBIAN_FRONTEND=noninteractive
apt-get -yq install portsentry > /dev/null
echo "Configuration de portsentry..."
sed -i 's/TCP_MODE="tcp"/TCP_MODE="atcp"/g' /etc/default/portsentry
sed -i 's/UDP_MODE="udp"/UDP_MODE="audp"/g' /etc/default/portsentry
sed -i 's/BLOCK_UDP="0"/BLOCK_UDP="1"/g' /etc/portsentry/portsentry.conf
sed -i 's/BLOCK_TCP="0"/BLOCK_TCP="1"/g' /etc/portsentry/portsentry.conf
systemctl restart portsentry

echo "Arrêt et désactivation des services non désirés..."
systemctl stop avahi-daemon 2> /dev/null
systemctl stop cups 2> /dev/null
systemctl stop cups-browsed 2> /dev/null
systemctl stop kmod 2> /dev/null
systemctl stop procps 2> /dev/null
systemctl stop rsyslog 2> /dev/null
systemctl stop udev 2> /dev/null
systemctl disable avahi-daemon 2> /dev/null
systemctl disable cups 2> /dev/null
systemctl disable cups-browsed 2> /dev/null
systemctl disable kmod 2> /dev/null
systemctl disable procps 2> /dev/null
systemctl disable rsyslog 2> /dev/null
systemctl disable udev 2> /dev/null

echo "Configuration du script de mise à jour..."
echo "#!/bin/sh" > /root/update_script.sh
echo "echo ----- $(date) ----- >> /var/log/update_script.log" >> /root/update_script.sh
echo "echo // apt-get update >> /var/log/update_script.log" >> /root/update_script.sh
echo "apt-get update >> /var/log/update_script.log" >> /root/update_script.sh
echo "echo // apt-get upgrade >> /var/log/update_script.log" >> /root/update_script.sh
echo "apt-get upgrade -y >> /var/log/update_script.log" >> /root/update_script.sh
echo "0 4 * * 1	root	sh /root/update_script.sh" >> /etc/crontab
echo "@reboot		root	sh /root/update_script.sh" >> /etc/crontab
systemctl restart cron

echo "Installation de mailutils..."
apt-get install -y mailutils > /dev/null

echo "Configuration du script de diff du crontab..."
cp /etc/crontab /root/crontab_diff
echo "#!/bin/sh" > /root/crontab_checker.sh
echo "CMD=\$(diff /root/crontab_diff /etc/crontab)" >> /root/crontab_checker.sh
echo 'if [ ! -z "$CMD" ]; then' >> /root/crontab_checker.sh
echo '        echo $CMD | mail -s "diff /etc/crontab" root' >> /root/crontab_checker.sh
echo "fi" >> /root/crontab_checker.sh
echo "cp /etc/crontab /root/crontab_diff" >> /root/crontab_checker.sh
echo "0 0 * * *	root	sh /root/crontab_checker.sh" >> /etc/crontab
systemctl restart cron

echo "Installation d'apache2 et de php..."
sudo apt-get install -y apache2 php > /dev/null

echo "Configuration du SSL sur apache2..."
openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/apache-selfsigned.key -out /etc/ssl/certs/apache-selfsigned.crt -subj "/C=FR/ST=42/L=Paris/O=42/CN=42" 2> /dev/null
sed -i 's/\/etc\/ssl\/certs\/ssl-cert-snakeoil.pem/\/etc\/ssl\/certs\/apache-selfsigned.crt/g' /etc/apache2/sites-available/default-ssl.conf
sed -i 's/\/etc\/ssl\/private\/ssl-cert-snakeoil.key/\/etc\/ssl\/private\/apache-selfsigned.key/g' /etc/apache2/sites-available/default-ssl.conf
sudo a2enmod ssl > /dev/null
sudo a2ensite default-ssl > /dev/null
sudo systemctl restart apache2
echo "Mise en place de la page de login..."
rm -rf /var/www/html/index.html
wget -q https://raw.githubusercontent.com/plcharriere/roger-skyline-1/master/index.php -O /var/www/html/index.php

echo "Déploiement terminé !"
