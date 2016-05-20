void EmulatorPimpl::intcc()
{
    auto flags = registers->get_flags();

    push_word(flags);
    push_word(registers->get(CS));
    push_word(registers->get(IP) + instr_length);

    flags &= ~(IF | TF);
    registers->set_flags(flags);

    // int 3
    auto new_cs = mem->read<uint16_t>(4 * 3 + 2);
    auto new_ip = mem->read<uint16_t>(4 * 3 + 0);

    registers->set(CS, new_cs);
    registers->set(IP, new_ip);
}