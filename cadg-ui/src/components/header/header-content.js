import React from 'react';
import { Menu } from 'semantic-ui-react';
import logo from '../../images/logo.svg'

const Header = () => {
  return (
    <div>
      <Menu>
        <Menu.Menu>
          <Menu.Item>
            <b>CADG</b><img src={logo} alt='logo'/><b>OS-WASABI</b>
          </Menu.Item>
        </Menu.Menu>

        <Menu.Menu position='right'>
          <Menu.Item>
            Welcome Guest!
          </Menu.Item>
          <Menu.Item>
            Login
          </Menu.Item>
        </Menu.Menu>
      </Menu>
    </div>
  );
};

export default Header;