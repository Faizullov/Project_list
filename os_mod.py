

import requests, json

from ansible_collections.openstack.cloud.plugins.module_utils.openstack import (OpenStackModule)
from ansible.module_utils.basic import AnsibleModule

class My_Class(OpenStackModule):
    argument_spec = dict(
            auth_url = dict(type = 'str', required = False),
            username = dict(type = 'str', required = False),
            project_id = dict(type = 'str', required = False),
            project_name = dict(type = 'str', required = False),
            user_domain_name = dict(type = 'str', required = False),
            password = dict(type = 'str', required = False),)
    def run(self):
        result = dict(changed=False, name1=dict(type='str'))
        module = AnsibleModule(supports_check_mode=True)
        attrs = {}
        attrs = self.check_versioned(**attrs)
        tmp = self.conn.network.security_groups(**attrs)
        tmp = [item if isinstance(item, dict) else item.to_dict() for item in tmp]
        names = {}
        for i in tmp:
            names['name'] = i['name']
        result['name1'] = names
        module.exit_json(**result)

def main():
    module = My_Class()
    module()

if __name__ == '__main__':
    main()