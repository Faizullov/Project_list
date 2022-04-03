from ansible_collections.openstack.cloud.plugins.module_utils.openstack import (OpenStackModule)
from ansible.module_utils.basic import AnsibleModule

class SecurityGroupInfoModule(OpenStackModule):
    def run(self):
        attrs1 = {}
        attrs = {}
        data = []
        changed = False
        ports = self.conn.search_ports()
        attrs1 = self.check_versioned(**attrs1)
        serv = self.conn.search_servers(**attrs1)
        attrs = self.check_versioned(**attrs)
        result = self.conn.network.security_groups(**attrs)
        save_serv_gr = dict()
        save_gr = []
        save_protocols = dict()
        save_serv_addresses = dict()
        save_port_range_max = dict()
        save_port_range_min = dict()
        save_serv_names = []
        save_addresses = []
        save_ip = dict ()

        for p in ports:         # заходим в ports
            save_addresses.append(p['mac_address'])
            save_ip[p['mac_address']] = p['dns_assignment'][0]['ip_address']
            data.append(p['dns_assignment'][0]['ip_address']) #собираю ip адреса 

        for item in result:         # заходим в sec group, все sec groups здесь
            if not isinstance(item, dict):
                item = item.to_dict()
            tmp_save = []   
            tmp_save_port_max = []
            tmp_save_port_min = []
            for j in item['security_group_rules']: # заходим в sec group rules
                if not isinstance(j, dict):
                    j.to_dict()
                tmp_save.append(j['protocol'])   # список протоколов
                tmp_save_port_max.append(j['port_range_max']) # список портов
                tmp_save_port_min.append(j['port_range_min']) # список портов
            save_port_range_max[item['name']] = tmp_save_port_max #словарь портов 1
            save_port_range_min[item['name']] = tmp_save_port_min #словарь портов 2
            save_protocols[item['name']] = tmp_save # словарь протоколов, ключ - имя sec group
            save_gr.append(item['name'])     #список имен sec group

        for tmp in serv:
            if not isinstance(tmp, dict): 
                tmp = tmp.to_dict()       # сервер в dict
            tmp_save_sec = []
            keys = list(tmp['addresses'].keys())
            keys2 = list(tmp['addresses'][keys[0]][0].keys()) # странный способ, можно проще? (доступ к port address)
            save_serv_addresses[tmp['name']] = tmp['addresses'][keys[0]][0][keys2[3]]
            for i in tmp['security_groups']:   # ф-ция для нахождения name для sec. group
                if not isinstance(i, dict):
                    i.to_dict()
                tmp_save_sec.append(i['name']) #список имен sec group для серверa
            save_serv_gr[tmp['name']] = tmp_save_sec #cловарь sec groups, ключ - имя сервера
            save_serv_names.append(tmp['name']) #cписок имен серверов
                
        for serv_name in save_serv_names:
            check = False
            tmp_save_ip = []
            tmp_save_ports = []
            list_of_groups = []
            for serv_gr in save_serv_gr[serv_name]:
                for gr in save_gr:
                    if serv_gr == gr:
                        cnt = 0
                        if gr not in list_of_groups:
                            list_of_groups.append(gr)
                            for protocols in save_protocols[gr]:
                                if protocols != None and save_port_range_max[gr][cnt] != None and save_port_range_min[gr][cnt]:
                                    if check == False:
                                        tmp_save_name = serv_name
                                        for address in save_addresses:
                                            if save_serv_addresses[serv_name] == address:
                                                tmp_save_ip.append(save_ip[address])
                                        check = True
                                    if save_port_range_max[gr][cnt] not in tmp_save_ports:
                                        tmp_save_ports.append(save_port_range_max[gr][cnt])
                                cnt = cnt + 1
            if check == True:
                data.append(tmp_save_name)
                data.append("ip:")
                data.append(tmp_save_ip)
                data.append("ports:")
                data.append(tmp_save_ports)
        self.exit_json(changed = changed, my_res = data)


def main():
    module = SecurityGroupInfoModule()
    module()


if __name__ == "__main__":
    main()