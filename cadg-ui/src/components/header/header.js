import React, { Component } from 'react';
import {
  Collapse,
  Navbar,
  NavbarToggler,
  NavbarBrand,
  Nav,
  NavItem,
  NavLink,
  UncontrolledDropdown,
  DropdownToggle,
  DropdownMenu,
  DropdownItem } from 'reactstrap';
import logo from '../../images/logo.svg';

export default class Header extends Component {
  constructor(props) {
    super(props);

    this.toggle = this.toggle.bind(this);
    this.state = {
      isOpen: false
    };
  }

  toggle() { this.setState({ isOpen: !this.state.isOpen }); }

  render() {
    return (
      <div>
        <Navbar color="dark" dark fixed='true' expand="md">
          <NavbarBrand href="/">
            <b>OS-WASABI</b> <img src={logo} alt='logo' height='42' width='42'/> CADG
          </NavbarBrand>
          <NavbarToggler onClick={this.toggle} />
          <Collapse isOpen={this.state.isOpen} navbar>
            <Nav className="ml-auto" navbar>

              {/*Alerts*/}
              <NavItem>
                <NavLink href="/alerts"><b>Alerts</b></NavLink>
              </NavItem>

              {/*Originators*/}
              <NavItem>
                <NavLink href="/originators"><b>Originators</b></NavLink>
              </NavItem>

              {/*Disseminators*/}
              <NavItem>
                <NavLink href="/disseminators"><b>Disseminators</b></NavLink>
              </NavItem>

              {/*Admins*/}
              <NavItem>
                <NavLink href="/admins"><b>Administrators</b></NavLink>
              </NavItem>

              {/*Login*/}
              <NavItem>
                <NavLink className='text-white' href="/login"><b>Login</b></NavLink>
              </NavItem>

            </Nav>
          </Collapse>
        </Navbar>
      </div>
    );
  }
}